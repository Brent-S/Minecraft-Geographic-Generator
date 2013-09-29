#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "EndianSwaps.h"
#include "NBTTagNew.h"

using namespace std;

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
	TagPayloadByte(char inChar){
		payload = inChar;
	}
	TagPayloadByte(istream inStream){
		payload = inStream.get();
	}
	string getDisplayString(){
		return string(payload); // TODO does this work reference wise?
	}
	iostream getStorageBytes(){
		iostream out;
		out << payload;
		return out;
	}
};

class TagPayloadShort : public TagPayload {
private:
	short payload;
public:
	TagPayloadShort(short inShort){
		payload = inShort;
	}
	TagPayloadShort(istream inStream){
		short inShort;
		inStream >> inShort;
		payload = EndianSwapShort(inShort);
	}
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << EndianSwapShort(payload);
		return out;
	}
};

class TagPayloadInt : public TagPayload {
private:
	int payload;
public:
	TagPayloadInt(int inInt){
		payload = inInt;
	}
	TagPayloadInt(istream inStream){
		int inInt;
		inStream >> inInt;
		payload = EndianSwapInt(inInt);
	}
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << EndianSwapInt(payload);
		return out;
	}
};

class TagPayloadLong : public TagPayload {
private:
	long payload;
public:
	TagPayloadLong(long inLong){
		payload = inLong;
	}
	TagPayloadLong(istream inStream){
		long inLong;
		inStream >> inLong;
		payload = EndianSwapLong(inLong);
	}
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << EndianSwapLong(payload);
		return out;
	}
};

class TagPayloadFloat : public TagPayload {
private:
	float payload;
public:
	TagPayloadFloat(float inFloat){
		payload = inFloat;
	}
	TagPayloadFloat(istream inStream){
		float inFloat;
		inStream >> inFloat;
		payload = EndianSwapFloat(inFloat);
	}
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << EndianSwapFloat(payload);
		return out;
	}
};

class TagPayloadDouble : public TagPayload {
private:
	double payload;
public:
	TagPayloadDouble(double inDouble){
		payload = inDouble;
	}
	TagPayloadDouble(istream inStream){
		double inDouble;
		inStream >> inDouble;
		payload = EndianSwapDouble(inDouble);
	}
	string getDisplayString(){
		stringstream ss;
		ss << payload;
		string out;
		ss >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << EndianSwapDouble(payload);
		return out;
	}
};

class TagPayloadByteArray : public TagPayload {
private:
	char* payload;
	int length;
public:
	TagPayloadByteArray(char* inArray, int inLength){
		length = inLength;
		for(int i = 0; i < length; i++){
			payload[i] = inArray[i];
		}
	}
	TagPayloadByteArray(istream inStream){
		int inLength;
		inStream >> inLength;
		length = EndianSwapInt(inLength);
		payload = new char[length];		// I don't know if it's necessary to check that this allocation has worked.
		for(int i = 0; i < length; i++){
			inStream >> payload[i];
		}
	}
	string getDisplayString(){
		stringstream OutStream;
		string out;
		for(int i = 0; i < length; i++){
			OutStream << payload[i];
		}
		OutStream >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << EndianSwapInt(length);
		for(int i = 0; i < length; i++){
			out << payload[i];
		}
		return out;
	}
	~TagPayloadByteArray(){
		delete [] payload;			// I think this is right...
	}
};

class TagPayloadString : public TagPayload {
private:
	string payload;
public:
	TagPayloadString(string inString){
		payload = inString;
	}
	TagPayloadString(istream inStream){
		int length;
		inStream >> length;
		char* inString = new char[length];
		for(int i = 0; i < length; i++){
			inStream >> inString[i];
		}
		payload = string(inString);
	}
	string getDisplayString(void){
		return payload;
	}
	iostream getStorageBytes(){
		unsigned short shortLength = (unsigned short) payload.size();  // This is right (I think) due to the weirdness of NBT
		iostream out;
		out << EndianSwapShort(shortLength) << payload;
		return out;
	}
};

class TagPayloadList : public TagPayload {
private:
	vector<TagPayload> payload;
	TAG_TypeID type;
public:
	TagPayloadList(TAG_TypeID inType){
		type = inType;
	}
	void addPayload(TagPayload* inPayload){
		payload.push_back(*inPayload);
	}
	TagPayloadList(istream inStream){
		char inType;
		inStream >> inType;
		int inLength;
		inStream >> inLength;
		int length = EndianSwapInt(inLength);
		for(int i = 0; i < length; i++){
			payload.push_back(getPayloadFromStream(inType,inStream));
		}
	}
	string getDisplayString(){
		stringstream ss;
		string out;
		ss << "List of " << TAGTypeToString(type) << ":/n";
		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
			ss <<"(" << it->getDisplayString() << ")\t";
		}
		ss << "/n";
		ss >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << ((unsigned char) type) << EndianSwapInt((int) payload.size);

		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
			out << (it->getStorageBytes()).rdbuf();
		}
		return out;
	}
};

class TagPayloadIntArray : public TagPayload {
private:
	int* payload;
	int length; // number of ints, not bytes.
public:
	TagPayloadIntArray(int* inArray, int inLength){
		length = inLength;
		for(int i = 0; i < length; i++){
			payload[i] = inArray[i];
		}
	}
	TagPayloadIntArray(istream inStream){
		int inLength;
		inStream >> inLength;
		length = EndianSwapInt(inLength);
		payload = new int[length];		// I don't know if it's necessary to check that this allocation has worked.
		for(int i = 0; i < length; i++){
			int temp;
			inStream >> temp;
			payload[i] = EndianSwapInt(temp);
		}
	}
	string getDisplayString(){
		stringstream OutStream;
		string out;
		for(size_t i = 0; i < length; i++){
			OutStream << payload[i];
		}
		OutStream >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		out << EndianSwapInt(length);
		for(int i = 0; i < length; i++){
			out << EndianSwapInt(payload[i]);
		}
		return out;
	}
};

class NBTTag {
private:
	TAG_TypeID TagType;
	TagPayloadString name;
	TagPayload* Payload; // Need to be careful about this.

public:
	NBTTag(istream inStream){
		char inType;
		inStream >> inType;
		TagType = static_cast<TAG_TypeID>(inType);
		name = TagPayloadString(inStream);
		Payload = getPayloadFromStream(TagType,inStream);
	}
	string getDisplayString(){
		return (TAGTypeToString(TagType) + " called \"" + name.getDisplayString() + "\" \{\n" + Payload->getDisplayString() + "\}\n");
	}
	iostream getStorageBytes(){
		iostream out;
		out << ( (unsigned short) TagType) << (name.getStorageBytes()).rdbuf() << (Payload->getStorageBytes()).rdbuf();
		return out;
	}
};


class TagPayloadCompound : public TagPayload {
private:
	vector<NBTTag> payload;
public:
	void addTag(NBTTag inTag){
		payload.push_back(inTag);
	}
	TagPayloadCompound(istream inStream){
		char nxtByte = inStream.peek();
		while(static_cast<TAG_TypeID>(nxtByte) != TAG_End){
			payload.push_back(NBTTag(inStream));
			nxtByte = inStream.peek();
		}
	}
	string getDisplayString(){
		stringstream ss;
		string out;
		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
			ss <<"(" << it->getDisplayString() << ")\t";
		}
		ss >> out;
		return out;
	}
	iostream getStorageBytes(){
		iostream out;
		for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
			out << (it->getStorageBytes()).rdbuf();
		}
		out << '0'; // TAG_End
		return out;
	}
};
