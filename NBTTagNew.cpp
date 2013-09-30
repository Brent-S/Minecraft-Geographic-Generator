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
void TagPayloadByte::getStorageBytes(iostream& inStream){
	//stringstream out;
	inStream << payload;
	//return out;
}

TagPayloadByte * TagPayloadByte::clone(){
	return new TagPayloadByte(payload);
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
void TagPayloadShort::getStorageBytes(iostream& inStream){
	inStream << EndianSwapShort(payload);
}

TagPayloadShort * TagPayloadShort::clone(){
	return new TagPayloadShort(payload);
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
void TagPayloadInt::getStorageBytes(iostream& inStream){
	inStream << EndianSwapInt(payload);
}
TagPayloadInt * TagPayloadInt::clone(){
	return new TagPayloadInt(payload);
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
void TagPayloadLong::getStorageBytes(iostream& inStream){
	inStream << EndianSwapLong(payload);
}
TagPayloadLong * TagPayloadLong::clone(){
	return new TagPayloadLong(payload);
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
void TagPayloadFloat::getStorageBytes(iostream& inStream){
	inStream << EndianSwapFloat(payload);
}
TagPayloadFloat * TagPayloadFloat::clone(){
	return new TagPayloadFloat(payload);
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
void TagPayloadDouble::getStorageBytes(iostream& inStream){
	inStream << EndianSwapDouble(payload);
}
TagPayloadDouble * TagPayloadDouble::clone(){
	return new TagPayloadDouble(payload);
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
void TagPayloadByteArray::getStorageBytes(iostream& inStream){
	inStream << EndianSwapInt(length);
	for(int i = 0; i < length; i++){
		inStream << payload[i];
	}
}
TagPayloadByteArray::~TagPayloadByteArray(){
	delete [] payload;	// I think this is right...
}
TagPayloadByteArray * TagPayloadByteArray::clone(){
	int newLength = length;
	char * newArray = new char[length];
	for(int i = 0; i < length; i++){
		newArray[i] = payload[i];
	}
	TagPayloadByteArray* out = new TagPayloadByteArray(newArray, newLength);
	delete [] newArray; // TODO check this
	return out;
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
void TagPayloadString::getStorageBytes(iostream& inStream){
	unsigned short shortLength = (unsigned short) payload.size(); // This is right (I think) due to the weirdness of NBT
	inStream << EndianSwapShort(shortLength) << payload;
}
TagPayloadString * TagPayloadString::clone(){
	return new TagPayloadString(payload);
}




TagPayloadList::TagPayloadList(TAG_TypeID inType){ // I hope the vector gets correctly initialised...
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
void TagPayloadList::getStorageBytes(iostream& inStream){
	inStream << ((unsigned char) type) << EndianSwapInt((int) payload.size());
	for(vector<TagPayload*>::iterator it = payload.begin(); it != payload.end(); ++it) {
		(*it)->getStorageBytes(inStream);
	}
}
void TagPayloadList::addManyPayloads(vector<TagPayload*> inVector){
	for(vector<TagPayload*>::iterator it = inVector.begin(); it != inVector.end(); ++it) {
		payload.push_back((*it)->clone());
	}
}
TagPayloadList * TagPayloadList::clone(){
	TagPayloadList* out = new TagPayloadList(type);
	out->addManyPayloads(payload);
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
void TagPayloadIntArray::getStorageBytes(iostream& inStream){
	inStream << EndianSwapInt(length);
	for(int i = 0; i < length; i++){
		inStream << EndianSwapInt(payload[i]);
	}
}
TagPayloadIntArray * TagPayloadIntArray::clone(){
	int newLength = length;
	int * newArray = new int[length];
	for(int i = 0; i < length; i++){
		newArray[i] = payload[i];
	}
	TagPayloadIntArray* out = new TagPayloadIntArray(newArray, newLength);
	delete [] newArray; // TODO check this
	return out;
}




NBTTag::NBTTag(istream& inStream) :
		TagType(static_cast<TAG_TypeID>(inStream.get())), name(inStream)	// This confuses me...
{
	Payload = getPayloadFromStream(TagType,inStream);
}
TagPayloadString NBTTag::nameClone(){
	return *(name.clone());
}
//NBTTag::NBTTag(NBTTag& inTag) : name(inTag.nameClone()){ // this looks odd to me...
//	// name = inTag.nameClone();
//	Payload = inTag.Payload->clone(); // TODO Check this
//}
string NBTTag::getDisplayString(){
	return (TAGTypeToString(TagType) + " called \"" + name.getDisplayString() + "\" {\n" + Payload->getDisplayString() + "}\n");
}
void NBTTag::getStorageBytes(iostream& inStream){
	inStream << ( (unsigned short) TagType);
	name.getStorageBytes(inStream);
	Payload->getStorageBytes(inStream);
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
	for(vector<NBTTag>::iterator it = payload.begin(); it != payload.end(); ++it) {
		ss <<"(" << (*it).getDisplayString() << ")\t";
	}
	ss >> out;
	return out;
}
void TagPayloadCompound::getStorageBytes(iostream& inStream){
	for(vector<NBTTag>::iterator it = payload.begin(); it != payload.end(); ++it) {
		it->getStorageBytes(inStream);
	}
	inStream << '0'; // TAG_End
}

