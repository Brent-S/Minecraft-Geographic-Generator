#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "EndianSwaps.h"
#include "NBTTagNew.h"

using namespace std;


TagPayloadByte::TagPayloadByte(char inChar){
	payload = inChar;
}
TagPayloadByte::TagPayloadByte(istream& inStream){
	payload = inStream.get();
}
string TagPayloadByte::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;		// TODO does this work reference wise?
}
iostream TagPayloadByte::getStorageBytes(){
	stringstream out;
	out << payload;
	return out;
}

TagPayloadShort::TagPayloadShort(short inShort){
	payload = inShort;
}
TagPayloadShort::TagPayloadShort(istream& inStream){
	short inShort;
	inStream >> inShort;
	payload = EndianSwapShort(inShort);
}
string TagPayloadShort::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
iostream TagPayloadShort::getStorageBytes(){
	stringstream out;
	out << EndianSwapShort(payload);
	return out;
}

TagPayloadInt::TagPayloadInt(int inInt){
	payload = inInt;
}
TagPayloadInt::TagPayloadInt(istream& inStream){
	int inInt;
	inStream >> inInt;
	payload = EndianSwapInt(inInt);
}
string TagPayloadInt::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
iostream TagPayloadInt::getStorageBytes(){
	stringstream out;
	out << EndianSwapInt(payload);
	return out;
}

TagPayloadLong::TagPayloadLong(long inLong){
	payload = inLong;
}
TagPayloadLong::TagPayloadLong(istream& inStream){
	long inLong;
	inStream >> inLong;
	payload = EndianSwapLong(inLong);
}
string TagPayloadLong::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
iostream TagPayloadLong::getStorageBytes(){
	stringstream out;
	out << EndianSwapLong(payload);
	return out;
}

TagPayloadFloat::TagPayloadFloat(float inFloat){
	payload = inFloat;
}
TagPayloadFloat::TagPayloadFloat(istream& inStream){
	float inFloat;
	inStream >> inFloat;
	payload = EndianSwapFloat(inFloat);
}
string TagPayloadFloat::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
iostream TagPayloadFloat::getStorageBytes(){
	stringstream out;
	out << EndianSwapFloat(payload);
	return out;
}

TagPayloadDouble::TagPayloadDouble(double inDouble){
	payload = inDouble;
}
TagPayloadDouble::TagPayloadDouble(istream& inStream){
	double inDouble;
	inStream >> inDouble;
	payload = EndianSwapDouble(inDouble);
}
string TagPayloadDouble::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
iostream TagPayloadDouble::getStorageBytes(){
	stringstream out;
	out << EndianSwapDouble(payload);
	return out;
}



TagPayloadByteArray::TagPayloadByteArray(char* inArray, int inLength){
	length = inLength;
	for(int i = 0; i < length; i++){
		payload[i] = inArray[i];
	}
}
TagPayloadByteArray::TagPayloadByteArray(istream& inStream){
	int inLength;
	inStream >> inLength;
	length = EndianSwapInt(inLength);
	payload = new char[length];	// I don't know if it's necessary to check that this allocation has worked.
	for(int i = 0; i < length; i++){
		inStream >> payload[i];
	}
}
string TagPayloadByteArray::getDisplayString(){
	stringstream OutStream;
	string out;
	for(int i = 0; i < length; i++){
		OutStream << payload[i];
	}
	OutStream >> out;
	return out;
}
iostream TagPayloadByteArray::getStorageBytes(){
	stringstream out;
	out << EndianSwapInt(length);
	for(int i = 0; i < length; i++){
		out << payload[i];
	}
	return out;
}
TagPayloadByteArray::~TagPayloadByteArray(){
	delete [] payload;	// I think this is right...
}

TagPayloadString::TagPayloadString(string inString){
	payload = inString;
}
TagPayloadString::TagPayloadString(istream& inStream){
	int length;
	inStream >> length;
	char* inString = new char[length];
	for(int i = 0; i < length; i++){
		inStream >> inString[i];
	}
	payload = string(inString);
}
string TagPayloadString::getDisplayString(void){
	return payload;
}
iostream TagPayloadString::getStorageBytes(){
	unsigned short shortLength = (unsigned short) payload.size(); // This is right (I think) due to the weirdness of NBT
	stringstream out;
	out << EndianSwapShort(shortLength) << payload;
	return out;
}



TagPayloadList::TagPayloadList(TAG_TypeID inType){
	type = inType;
}
void TagPayloadList::addPayload(TagPayload* inPayload){
	payload.push_back(inPayload);
}
TagPayloadList::TagPayloadList(istream& inStream){
	char inType;
	inStream >> inType;
	int inLength;
	inStream >> inLength;
	int length = EndianSwapInt(inLength);
	for(int i = 0; i < length; i++){
		payload.push_back(getPayloadFromStream(inType,inStream));
	}
}
string TagPayloadList::getDisplayString(){
	stringstream ss;
	string out;
	ss << "List of " << TAGTypeToString(type) << ":/n";
	for(vector<TagPayload*>::iterator it = payload.begin(); it != payload.end(); ++it) {
		ss <<"(" << (*it)->getDisplayString() << ")\t";
	}
	ss << "/n";
	ss >> out;
	return out;
}
iostream TagPayloadList::getStorageBytes(){
	stringstream out;
	out << ((unsigned char) type) << EndianSwapInt((int) payload.size());

	for(vector<TagPayload*>::iterator it = payload.begin(); it != payload.end(); ++it) {
		out << ((*it)->getStorageBytes()).rdbuf();
	}
	return out;
}



TagPayloadIntArray::TagPayloadIntArray(int* inArray, int inLength){
	length = inLength;
	for(int i = 0; i < length; i++){
		payload[i] = inArray[i];
	}
}
TagPayloadIntArray::TagPayloadIntArray(istream& inStream){
	int inLength;
	inStream >> inLength;
	length = EndianSwapInt(inLength);
	payload = new int[length];	// I don't know if it's necessary to check that this allocation has worked.
	for(int i = 0; i < length; i++){
		int temp;
		inStream >> temp;
		payload[i] = EndianSwapInt(temp);
	}
}
string TagPayloadIntArray::getDisplayString(){
	stringstream OutStream;
	string out;
	for(int i = 0; i < length; i++){
		OutStream << payload[i];
	}
	OutStream >> out;
	return out;
}
iostream TagPayloadIntArray::getStorageBytes(){
	stringstream out;
	out << EndianSwapInt(length);
	for(int i = 0; i < length; i++){
		out << EndianSwapInt(payload[i]);
	}
	return out;
}


NBTTag::NBTTag(istream& inStream) :
		TagType(static_cast<TAG_TypeID>(inStream.get())), name(inStream)	// This confuses me...
{
//	char inType;
//	inStream >> inType;
//	TagType = static_cast<TAG_TypeID>(inType);
//	name = TagPayloadString(inStream);
	Payload = getPayloadFromStream(TagType,inStream);
}
string NBTTag::getDisplayString(){
	return (TAGTypeToString(TagType) + " called \"" + name.getDisplayString() + "\" {\n" + Payload->getDisplayString() + "}\n");
}
iostream NBTTag::getStorageBytes(){
	stringstream out;
	out << ( (unsigned short) TagType) << (name.getStorageBytes()).rdbuf() << (Payload->getStorageBytes()).rdbuf();
	return out;
}




void TagPayloadCompound::addTag(NBTTag inTag){
	payload.push_back(inTag);
}
TagPayloadCompound::TagPayloadCompound(istream& inStream){
	char nxtByte = inStream.peek();
	while(static_cast<TAG_TypeID>(nxtByte) != TAG_End){
		payload.push_back(NBTTag(inStream));
		nxtByte = inStream.peek();
	}
}
string TagPayloadCompound::getDisplayString(){
	stringstream ss;
	string out;
	for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
		ss <<"(" << it->getDisplayString() << ")\t";
	}
	ss >> out;
	return out;
}
iostream TagPayloadCompound::getStorageBytes(){
	stringstream out;
	for(vector<TagPayload>::iterator it = payload.begin(); it != payload.end(); ++it) {
		out << (it->getStorageBytes()).rdbuf();
	}
	out << '0'; // TAG_End
	return out;
}

