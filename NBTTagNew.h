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

// I do not know if the following signature definition thingies are necessary (or even compile...)

class TagPayload {
public:
	virtual string getDisplayString() =0;	// TODO Need to check how polymorphic inheritance works
	virtual iostream getStorageBytes() =0;
	virtual ~TagPayload();					// I hope this is correct...
};

class TagPayloadByte : public TagPayload {
private:
	char payload;
public:
	TagPayloadByte(char inChar);
	TagPayloadByte(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadShort : public TagPayload {
private:
	short payload;
public:
	TagPayloadShort(short inShort);
	TagPayloadShort(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadInt : public TagPayload {
private:
	int payload;
public:
	TagPayloadInt(int inInt);
	TagPayloadInt(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadLong : public TagPayload {
private:
	long payload;
public:
	TagPayloadLong(long inLong);
	TagPayloadLong(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadFloat : public TagPayload {
private:
	float payload;
public:
	TagPayloadFloat(float inFloat);
	TagPayloadFloat(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadDouble : public TagPayload {
private:
	double payload;
public:
	TagPayloadDouble(double inDouble);
	TagPayloadDouble(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadByteArray : public TagPayload {
private:
	char* payload;
	int length;
public:
	TagPayloadByteArray(char* inArray, int inLength);
	TagPayloadByteArray(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
	~TagPayloadByteArray();
};

class TagPayloadString : public TagPayload {
private:
	string payload;
public:
	TagPayloadString(string inString);
	TagPayloadString(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadList : public TagPayload {
private:
	vector<TagPayload> payload;
	TAG_TypeID type;
public:
	TagPayloadList(TAG_TypeID inType);
	void addPayload(TagPayload* inPayload);
	TagPayloadList(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class TagPayloadIntArray : public TagPayload {
private:
	int* payload;
	int length; // number of ints, not bytes.
public:
	TagPayloadIntArray(int* inArray, int inLength);
	TagPayloadIntArray(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

class NBTTag {
private:
	const TAG_TypeID TagType;
	TagPayloadString name;
	TagPayload* Payload; // Need to be careful about this.
public:
	NBTTag(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};


class TagPayloadCompound : public TagPayload {
private:
	vector<NBTTag> payload;
public:
	void addTag(NBTTag inTag);
	TagPayloadCompound(istream inStream);
	string getDisplayString();
	iostream getStorageBytes();
};

// I DO know that the rest IS necessary.

TagPayload getPayloadFromStream(TAG_TypeID inType, istream inStream){		// TODO check whether the polymorphism works here
																			// or if pointers are needed...
		switch (inType)
		{
		case TAG_End: return NULL;
		break;
		case TAG_Byte: return TagPayloadByte(inStream);
		break;
		case TAG_Short: return TagPayloadShort(inStream);
		break;
		case TAG_Int: return TagPayloadInt(inStream);
		break;
		case TAG_Long: return TagPayloadLong(inStream);
		break;
		case TAG_Float: return TagPayloadFloat(inStream);
		break;
		case TAG_Double: return TagPayloadDouble(inStream);
		break;
		case TAG_Byte_Array: return TagPayloadByteArray(inStream);
		break;
		case TAG_String: return TagPayloadString(inStream);
		break;
		case TAG_List: return TagPayloadList(inStream);
		break;
		case TAG_Compound: return TagPayloadCompound(inStream);
		break;
		case TAG_IntArray: return TagPayloadIntArray(inStream);
		break;
		}
		return NULL;
}

TagPayload getPayloadFromStream(int inType, istream inStream){
	TAG_TypeID changed = static_cast<TAG_TypeID>(inType);
	return getPayloadFromStream(changed, inStream);
}

