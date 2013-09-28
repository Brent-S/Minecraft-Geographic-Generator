#include<cstdlib>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

enum TAG_TypeID {TAG_End, TAG_Byte, TAG_Short, TAG_Int, TAG_Long, TAG_Float, TAG_Double,
	TAG_Byte_Array, TAG_String, TAG_List, TAG_Compound, TAG_IntArray };

string TAGTypeToString(TAG_TypeID inID){
	string out = "UNKNOWN";
	switch (inID)
	{
	case TAG_End: out = "TAG_End";
	    break;
	case TAG_Byte: out = "TAG_Byte";
	    break;
	case TAG_Short: out = "TAG_Short";
	    break;
	case TAG_Int: out = "TAG_Int";
	    break;
	case TAG_Long: out = "TAG_Long";
	    break;
	case TAG_Float: out = "TAG_Float";
	    break;
	case TAG_Double: out = "TAG_Double";
	    break;
	case TAG_Byte_Array: out = "TAG_Byte_Array";
	    break;
	case TAG_String: out = "TAG_String";
	    break;
	case TAG_List: out = "TAG_List";
	    break;
	case TAG_Compound: out = "TAG_Compound";
	    break;
	case TAG_IntArray: out = "TAG_IntArray";
	    break;
	}
	return out;
}


class TagPayload {
public:
	virtual string getDisplayString() =0;	// TODO Need to check how polymorphic inheritance works
	virtual istream getStorageBytes() =0;
	virtual ~TagPayload();					// I hope this is correct...
};

class TagPayloadByte : public TagPayload {
private:
	char payload;
public:
	TagPayloadByte(string inString){
		payload = inString;
	}
	string getDisplayString(){
		return string(payload); // TODO does this work reference wise?
	}
	istream getStorageBytes(){
		istream out;
		out << payload;
		return out;
	}
};

class TagPayloadShort : public TagPayload {
private:
	short payload;
public:
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	istream getStorageBytes(){
		union {
			short payShort = payload;
			struct {
				unsigned char first;
				unsigned char second;
			} uchar;
		} EndianSwapper;
		istream out;
		out << EndianSwapper.uchar.second << EndianSwapper.uchar.first;
		return out;
	}
};

class TagPayloadInt : public TagPayload {
private:
	int payload;
public:
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	istream getStorageBytes(){
		union {
			int payInt = payload;
			struct {
				unsigned char first;
				unsigned char second;
				unsigned char third;
				unsigned char fourth;
			} uchar;
		} EndianSwapper;
		istream out;
		out << EndianSwapper.uchar.fourth << EndianSwapper.uchar.third << EndianSwapper.uchar.second << EndianSwapper.uchar.first;
		return out;
	}
};

class TagPayloadLong : public TagPayload {
private:
	long payload;
public:
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	istream getStorageBytes(){
		union {
			long payLong = payload;
			struct {
				unsigned char first;
				unsigned char second;
				unsigned char third;
				unsigned char fourth;
				unsigned char fifth;
				unsigned char sixth;
				unsigned char seventh;
				unsigned char eigth;
			} uchar;
		} EndianSwapper;
		istream out;
		out << EndianSwapper.uchar.eigth << EndianSwapper.uchar.seventh << EndianSwapper.uchar.sixth << EndianSwapper.uchar.fifth
				<< EndianSwapper.uchar.fourth << EndianSwapper.uchar.third << EndianSwapper.uchar.second << EndianSwapper.uchar.first;
		return out;
	}
};

class TagPayloadFloat : public TagPayload {
private:
	float payload;
public:
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	istream getStorageBytes(){
		union {
			float payFloat = payload;
			struct {
				unsigned char first;
				unsigned char second;
				unsigned char third;
				unsigned char fourth;
			} uchar;
		} EndianSwapper;
		istream out;
		out << EndianSwapper.uchar.fourth << EndianSwapper.uchar.third << EndianSwapper.uchar.second << EndianSwapper.uchar.first;
		return out;
	}
};

class TagPayloadDouble : public TagPayload {
private:
	double payload;
public:
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	istream getStorageBytes(){
		union {
			double payDouble = payload;
			struct {
				unsigned char first;
				unsigned char second;
				unsigned char third;
				unsigned char fourth;
				unsigned char fifth;
				unsigned char sixth;
				unsigned char seventh;
				unsigned char eigth;
			} uchar;
		} EndianSwapper;
		istream out;
		out << EndianSwapper.uchar.eigth << EndianSwapper.uchar.seventh << EndianSwapper.uchar.sixth << EndianSwapper.uchar.fifth
				<< EndianSwapper.uchar.fourth << EndianSwapper.uchar.third << EndianSwapper.uchar.second << EndianSwapper.uchar.first;
		return out;
	}
};

class TagPayloadByteArray : public TagPayload {
private:
	char* payload;
	int length;
public:
	string getDisplayString(){
		stringstream OutStream;
		string out;
		for(int i = 0; i < length; i++){
			OutStream << payload[i];
		}
		OutStream >> out;
		return out;
	}
	istream getStorageBytes(){
		union {
			int payInt = length;
			struct {
				unsigned char first;
				unsigned char second;
				unsigned char third;
				unsigned char fourth;
			} uchar;
		} EndianSwapper;
		istream out;
		out << EndianSwapper.uchar.fourth << EndianSwapper.uchar.third << EndianSwapper.uchar.second << EndianSwapper.uchar.first;
		for(int i = 0; i < length; i++){
			out << payload[i];
		}
		return out;
	}
};

class TagPayloadString : public TagPayload {
private:
	string payload;
public:
	TagPayloadString(string inString){
		payload = inString;
	}
	string getDisplayString(void){
		return payload;
	}
	istream getStorageBytes(){
		stringstream out;
		union {
			unsigned short ushort;
			struct {
				unsigned char first;
				unsigned char second;
			} uchar;
		} length;
		length.ushort = (unsigned short) payload.size();  // This is right (I think) due to the weirdness of NBT
		out << length.uchar.second << length.uchar.first << payload; // TODO check that this is endian correct...
		return out;
	}
};

class TagPayloadList : public TagPayload {
private:
	vector<TagPayload> payload;
	TAG_TypeID type;
	int length;
public:
	string getDisplayString(){
		stringstream ss;
		string out;
		ss << "List of " << TAGTypeToString(type) << ":/n";
		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
		    ss <<"(" << (*it).getDisplayString() << ")\t";
		}
		ss << "/n";
		ss >> out;
		return out;
	}
	istream getStorageBytes(){
		istream out;
		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
		    out << (*it).getStorageBytes();
		}
		return out;
	}
};

class TagPayloadIntArray : public TagPayload {
private:
	int* payload;
	int length; // number of ints, not bytes.
public:
	string getDisplayString(){
		stringstream OutStream;
		string out;
		for(size_t i = 0; i < length; i++){
			OutStream << payload[i];
		}
		OutStream >> out;
		return out;
	}
	istream getStorageBytes(){
		union {
			int payInt = length;
			struct {
				unsigned char first;
				unsigned char second;
				unsigned char third;
				unsigned char fourth;
			} uchar;
		} EndianSwapper;
		istream out;
		out << EndianSwapper.uchar.fourth << EndianSwapper.uchar.third << EndianSwapper.uchar.second << EndianSwapper.uchar.first;
		for(int i = 0; i < length; i++){
			out << payload[i];
		}
		return out;
	}
};

class NBTTag {
private:
	const TAG_TypeID TagType;
	TagPayloadString name;
	TagPayload* Payload; // Need to be careful about this.

public:
	string getDisplayString(){
		return (TAGTypeToString(TagType) + " called \"" + name.getDisplayString() + "\" \{\n" + Payload->getDisplayString() + "\}\n");
	}
	istream getStorageBytes(){
		istream out;
		out << ( (unsigned short) TagType) << name.getStorageBytes() << Payload->getStorageBytes();
		return out;
	}
};


class TagPayloadCompound : public TagPayload {
private:
	vector<NBTTag> payload;
public:
	string getDisplayString(){
		stringstream ss;
		string out;
		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
		    ss <<"(" << (*it).getDisplayString() << ")\t";
		}
		ss >> out;
		return out;
	}
	istream getStorageBytes(){
		istream out;
		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
		    out << (*it).getStorageBytes();
		}
		out << '0'; // TAG_End
		return out;
	}
};
