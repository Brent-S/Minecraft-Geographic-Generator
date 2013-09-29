// This file has been replaced by NBTTagNew.cpp


// DO NOT USE THIS FILE. It has been kept temporarily until it is known to no longer be needed.







#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "EndianSwaps.h"

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
//
//short EndianSwapShort(const short inShort){
//   short out;
//   char *shortToConvert = (char*) & inShort;
//   char *returnShort = (char*) & out;
//
//   returnShort[0] = shortToConvert[1];
//   returnShort[1] = shortToConvert[0];
//
//   return out;
//}
//
//int EndianSwapInt(const int inInt){
//   int out;
//   char *intToConvert = (char*) & inInt;
//   char *returnInt = (char*) & out;
//
//   returnInt[0] = intToConvert[3];
//   returnInt[1] = intToConvert[2];
//   returnInt[2] = intToConvert[1];
//   returnInt[3] = intToConvert[0];
//
//   return out;
//}
//
//long EndianSwapLong(const long inLong){
//   long out;
//   char *longToConvert = (char*) & inLong;
//   char *returnLong = (char*) & out;
//
//   returnLong[0] = longToConvert[7];
//   returnLong[1] = longToConvert[6];
//   returnLong[2] = longToConvert[5];
//   returnLong[3] = longToConvert[4];
//   returnLong[4] = longToConvert[3];
//   returnLong[5] = longToConvert[2];
//   returnLong[6] = longToConvert[1];
//   returnLong[7] = longToConvert[0];
//
//   return out;
//}
//
//float EndianSwapFloat(const float inFloat){
//   float out;
//   char *floatToConvert = (char*) & inFloat;
//   char *returnFloat = (char*) & out;
//
//   returnFloat[0] = floatToConvert[3];
//   returnFloat[1] = floatToConvert[2];
//   returnFloat[2] = floatToConvert[1];
//   returnFloat[3] = floatToConvert[0];
//
//   return out;
//}
//
//double EndianSwapDouble(const double inDouble){
//   double out;
//   char *doubleToConvert = (char*) & inDouble;
//   char *returnDouble = (char*) & out;
//
//   returnDouble[0] = doubleToConvert[7];
//   returnDouble[1] = doubleToConvert[6];
//   returnDouble[2] = doubleToConvert[5];
//   returnDouble[3] = doubleToConvert[4];
//   returnDouble[4] = doubleToConvert[3];
//   returnDouble[5] = doubleToConvert[2];
//   returnDouble[6] = doubleToConvert[1];
//   returnDouble[7] = doubleToConvert[0];
//
//   return out;
//}


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
		union {
			int payInt = length;
			struct {
				unsigned char first;
				unsigned char second;
				unsigned char third;
				unsigned char fourth;
			} uchar;
		} EndianSwapper;
		iostream out;
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
