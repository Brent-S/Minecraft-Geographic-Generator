#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

enum TAG_TypeID {TAG_End, TAG_Byte, TAG_Short, TAG_Int, TAG_Long, TAG_Float, TAG_Double,
	TAG_Byte_Array, TAG_String, TAG_List, TAG_Compound, TAG_IntArray };

string TAGTypeToString(TAG_TypeID inID);

class TagPayload {
public:
	virtual string getDisplayString() = 0;	// TODO Need to check how polymorphic inheritance works
	virtual void getStorageBytes(iostream& inStream) = 0;
	virtual TagPayload * clone() = 0;
	virtual ~TagPayload() {					// I hope this is correct...

	}
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
	~TagPayloadByte();
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
	~TagPayloadShort();
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
	~TagPayloadInt();
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
	~TagPayloadLong();
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
	~TagPayloadFloat();
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
	~TagPayloadDouble();
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
	~TagPayloadString();
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
	~TagPayloadList();
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
	~TagPayloadIntArray();
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
	~NBTTag();
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
	~TagPayloadCompound();
};

// I DO know that the rest IS necessary.

TagPayload * getPayloadFromStream(TAG_TypeID inType, istream& inStream);
TagPayload * getPayloadFromStream(int inType, istream& inStream);
