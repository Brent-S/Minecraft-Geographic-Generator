#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

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
	virtual string getDisplayString() = 0;	// TODO Need to check how polymorphic inheritance works
	virtual void getStorageBytes(iostream& inStream) = 0;
	virtual ~TagPayload();					// I hope this is correct...
	virtual TagPayload * clone() = 0;
};

class TagPayloadByte : public TagPayload {
private:
	char payload;
public:
	TagPayloadByte(char inChar);
	TagPayloadByte(istream& inStream);
	TagPayloadByte * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadShort : public TagPayload {
private:
	short payload;
public:
	TagPayloadShort(short inShort);
	TagPayloadShort(istream& inStream);
	TagPayloadShort * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadInt : public TagPayload {
private:
	int payload;
public:
	TagPayloadInt(int inInt);
	TagPayloadInt(istream& inStream);
	TagPayloadInt * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadLong : public TagPayload {
private:
	long payload;
public:
	TagPayloadLong(long inLong);
	TagPayloadLong(istream& inStream);
	TagPayloadLong * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadFloat : public TagPayload {
private:
	float payload;
public:
	TagPayloadFloat(float inFloat);
	TagPayloadFloat(istream& inStream);
	TagPayloadFloat * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadDouble : public TagPayload {
private:
	double payload;
public:
	TagPayloadDouble(double inDouble);
	TagPayloadDouble(istream& inStream);
	TagPayloadDouble * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadByteArray : public TagPayload {
private:
	char* payload;
	int length;
public:
	TagPayloadByteArray(char* inArray, int inLength);
	TagPayloadByteArray(istream& inStream);
	TagPayloadByteArray * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
	~TagPayloadByteArray();
};

class TagPayloadString : public TagPayload {
private:
	string payload;
public:
	TagPayloadString(string inString);
	TagPayloadString(istream& inStream);
	TagPayloadString * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadList : public TagPayload {
private:
	vector<TagPayload*> payload;
	TAG_TypeID type;
public:
	TagPayloadList(TAG_TypeID inType);
	void addPayload(TagPayload* inPayload);
	void addManyPayloads(vector<TagPayload*> inVector);
	TagPayloadList(istream& inStream);
	TagPayloadList * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class TagPayloadIntArray : public TagPayload {
private:
	int* payload;
	int length; // number of ints, not bytes.
public:
	TagPayloadIntArray(int* inArray, int inLength);
	TagPayloadIntArray(istream& inStream);
	TagPayloadIntArray * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

class NBTTag {
private:
	TAG_TypeID TagType;
	TagPayloadString name;
	TagPayload* Payload; // Need to be careful about this.
public:
	NBTTag(istream& inStream);
	//NBTTag(NBTTag& inTag);
	TagPayloadString nameClone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};


class TagPayloadCompound : public TagPayload {
private:
	vector<NBTTag> payload;
public:
	void addTag(NBTTag inTag);
	TagPayloadCompound(istream& inStream);
	TagPayloadCompound * clone();
	string getDisplayString();
	void getStorageBytes(iostream& inStream);
};

// I DO know that the rest IS necessary.

TagPayload * getPayloadFromStream(TAG_TypeID inType, istream& inStream){		// TODO check whether the polymorphism works here
																			 //or if pointers are needed...
		switch (inType)
		{
		case TAG_End: return (TagPayload *) NULL;
		break;
		case TAG_Byte: return new TagPayloadByte(inStream);
		break;
		case TAG_Short: return new TagPayloadShort(inStream);
		break;
		case TAG_Int: return new TagPayloadInt(inStream);
		break;
		case TAG_Long: return new TagPayloadLong(inStream);
		break;
		case TAG_Float: return new TagPayloadFloat(inStream);
		break;
		case TAG_Double: return new TagPayloadDouble(inStream);
		break;
		case TAG_Byte_Array: return new TagPayloadByteArray(inStream);
		break;
		case TAG_String: return new TagPayloadString(inStream);
		break;
		case TAG_List: return new TagPayloadList(inStream);
		break;
		case TAG_Compound: return new TagPayloadCompound(inStream);
		break;
		case TAG_IntArray: return new TagPayloadIntArray(inStream);
		break;
		}
		return (TagPayload *) NULL;
}

TagPayload * getPayloadFromStream(int inType, istream& inStream){
	TAG_TypeID changed = static_cast<TAG_TypeID>(inType);
	return getPayloadFromStream(changed, inStream);
}

