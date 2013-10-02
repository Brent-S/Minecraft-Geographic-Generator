#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "EndianSwaps.h"
#include "NBTTagNew.h"
#include <iostream> // TODO TEMPORARY
#include <bitset> // TODO TEMPORARY

using namespace std;


TagPayload::~TagPayload(){

}


TagPayloadByte::TagPayloadByte(char inChar){
	payload = inChar;
}
TagPayloadByte::TagPayloadByte(istream& inStream): payload(inStream.get()){

}
string TagPayloadByte::getDisplayString(){
	stringstream ss;
	ss << payload;
	ss.flush();
	string out;
	ss >> out;
	return out;
}
void TagPayloadByte::getStorageBytes(iostream& inStream){
	inStream << payload;
	inStream.flush();
}
TagPayloadByte * TagPayloadByte::clone(){
	return new TagPayloadByte(payload);
}
TagPayloadByte::~TagPayloadByte(){

}




TagPayloadShort::TagPayloadShort(short inShort){
	payload = inShort;
}
TagPayloadShort::TagPayloadShort(istream& inStream){
	payload = getSwappedShortFromStream(inStream);
}
string TagPayloadShort::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
void TagPayloadShort::getStorageBytes(iostream& inStream){
	writeSwappedShortToStream(payload, inStream);
	inStream.flush();
}

TagPayloadShort * TagPayloadShort::clone(){
	return new TagPayloadShort(payload);
}
TagPayloadShort::~TagPayloadShort(){

}




TagPayloadInt::TagPayloadInt(int inInt){
	payload = inInt;
}
TagPayloadInt::TagPayloadInt(istream& inStream){
	payload = getSwappedIntFromStream(inStream);
}
string TagPayloadInt::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
void TagPayloadInt::getStorageBytes(iostream& inStream){
	writeSwappedIntToStream(payload, inStream);
	inStream.flush();
}
TagPayloadInt * TagPayloadInt::clone(){
	return new TagPayloadInt(payload);
}
TagPayloadInt::~TagPayloadInt(){

}




TagPayloadLong::TagPayloadLong(long inLong){
	payload = inLong;
}
TagPayloadLong::TagPayloadLong(istream& inStream){
	payload = getSwappedLongFromStream(inStream);
}
string TagPayloadLong::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
void TagPayloadLong::getStorageBytes(iostream& inStream){
	writeSwappedLongToStream(payload, inStream);
}
TagPayloadLong * TagPayloadLong::clone(){
	return new TagPayloadLong(payload);
}
TagPayloadLong::~TagPayloadLong(){

}



TagPayloadFloat::TagPayloadFloat(float inFloat){
	payload = inFloat;
}
TagPayloadFloat::TagPayloadFloat(istream& inStream){
	payload = getSwappedFloatFromStream(inStream);
}
string TagPayloadFloat::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
void TagPayloadFloat::getStorageBytes(iostream& inStream){
	writeSwappedFloatToStream(payload, inStream);
	inStream.flush();
}
TagPayloadFloat * TagPayloadFloat::clone(){
	return new TagPayloadFloat(payload);
}
TagPayloadFloat::~TagPayloadFloat(){

}




TagPayloadDouble::TagPayloadDouble(double inDouble){
	payload = inDouble;
}
TagPayloadDouble::TagPayloadDouble(istream& inStream){
	payload = getSwappedDoubleFromStream(inStream);
}
string TagPayloadDouble::getDisplayString(){
	stringstream ss;
	ss << payload;
	string out;
	ss >> out;
	return out;
}
void TagPayloadDouble::getStorageBytes(iostream& inStream){
	writeSwappedDoubleToStream(payload, inStream);
	inStream.flush();
}
TagPayloadDouble * TagPayloadDouble::clone(){
	return new TagPayloadDouble(payload);
}
TagPayloadDouble::~TagPayloadDouble(){

}




TagPayloadByteArray::TagPayloadByteArray(char* inArray, int inLength){
	length = inLength;
	payload = new char[length];
	for(int i = 0; i < length; i++){
		payload[i] = inArray[i];
	}
}
TagPayloadByteArray::TagPayloadByteArray(istream& inStream){
	length = getSwappedIntFromStream(inStream);
	payload = new char[length];	// I don't know if it's necessary to check that this allocation has worked.
	for(int i = 0; i < length; i++){
		payload[i] = inStream.get();
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
	inStream.flush();
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
	unsigned short length = getSwappedShortFromStream(inStream);
	payload = getStringFromStream(inStream, length);
	//cout << "String payload created with content :" << payload << endl;
}
string TagPayloadString::getDisplayString(void){
	//cout << "TagPayload String display called" << endl;
	return payload;
}
void TagPayloadString::getStorageBytes(iostream& inStream){
	writeSwappedShortToStream((unsigned short) payload.size(), inStream);
	inStream << payload;
	inStream.flush();
}
TagPayloadString * TagPayloadString::clone(){
	return new TagPayloadString(payload);
}
TagPayloadString::~TagPayloadString(){
	// I'm not aware of any necessary deallocation
}



TagPayloadList::TagPayloadList(TAG_TypeID inType){ // I hope the vector gets correctly initialised...
	type = inType;
}
void TagPayloadList::addPayload(TagPayload* inPayload){
	payload.push_back(inPayload);
}
TagPayloadList::TagPayloadList(istream& inStream){
	char inType = inStream.get();
	type = static_cast<TAG_TypeID>(inType);
	int length = getSwappedIntFromStream(inStream);
	for(int i = 0; i < length; i++){
		payload.push_back(getPayloadFromStream(type,inStream));
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
	inStream << getCharFromTag(type);
	writeSwappedIntToStream((int) payload.size(), inStream);
	for(vector<TagPayload*>::iterator it = payload.begin(); it != payload.end(); ++it) {
		(*it)->getStorageBytes(inStream);
	}
	inStream.flush();
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
TagPayloadList::~TagPayloadList(){

}




TagPayloadIntArray::TagPayloadIntArray(int* inArray, int inLength){
	length = inLength;
	payload = new int[length];
	for(int i = 0; i < length; i++){
		payload[i] = inArray[i];
	}
}
TagPayloadIntArray::TagPayloadIntArray(istream& inStream){
	length = getSwappedIntFromStream(inStream);
	payload = new int[length];	// I don't know if it's necessary to check that this allocation has worked.
	for(int i = 0; i < length; i++){
		payload[i] = getSwappedIntFromStream(inStream);
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
		writeSwappedIntToStream(payload[i], inStream);
	}
	inStream.flush();
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
TagPayloadIntArray::~TagPayloadIntArray(){
	delete [] payload;
}




NBTTag::NBTTag(istream& inStream) :
								TagType(static_cast<TAG_TypeID>(inStream.get())), name(inStream)	// This confuses me...
{
	Payload = getPayloadFromStream(TagType,inStream);
	string pause;
	cout << "Pause" << endl;
	cin >> pause;
}
TagPayloadString NBTTag::nameClone(){
	return *(name.clone());
}
string NBTTag::getDisplayString(){
	string nameString = name.getDisplayString();
	string payloadString = (*Payload).getDisplayString();
	string out = (TAGTypeToString(TagType) + " named \"" + nameString + "\"\n{" + payloadString + "}\n");
	return out;
}
void NBTTag::getStorageBytes(iostream& inStream){
	inStream << getCharFromTag(TagType);
	name.getStorageBytes(inStream);
	Payload->getStorageBytes(inStream);
	inStream.flush();
}
NBTTag::~NBTTag(){
	//delete Payload; //TODO very confused now...
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
TagPayloadCompound::TagPayloadCompound(){

}
string TagPayloadCompound::getDisplayString(){
	string out;
	for(vector<NBTTag>::iterator it = payload.begin(); it != payload.end(); it++) { // TODO  ++it?
		out += string("(") + (*it).getDisplayString() + ")\t";
	}
	return out;
}
void TagPayloadCompound::getStorageBytes(iostream& inStream){
	for(vector<NBTTag>::iterator it = payload.begin(); it != payload.end(); it++) {
		it->getStorageBytes(inStream);
	}
	inStream << (unsigned char) 0; // TAG_End
	inStream.flush();
}
void TagPayloadCompound::addManyTags(vector<NBTTag>& inVector){
	for(vector<NBTTag>::iterator it = inVector.begin(); it != inVector.end(); it++) {
		payload.push_back(*it);
	}
}

TagPayloadCompound * TagPayloadCompound::clone(){
	TagPayloadCompound* out = new TagPayloadCompound;
	out->addManyTags(payload);
	return out;
}
TagPayloadCompound::~TagPayloadCompound(){

}





TagPayload * getPayloadFromStream(TAG_TypeID inType, istream& inStream){
	// cout << "Constructing Payload of type" << TAGTypeToString(inType) << endl;
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


short getSwappedShortFromStream(istream& inStream){
	short out;
	char *returnShort = (char*) & out;
	returnShort[1] = inStream.get();
	returnShort[0] = inStream.get();
	return out;
}
int getSwappedIntFromStream(istream& inStream){
	int out;
	char *returnInt = (char*) & out;
	returnInt[3] = inStream.get();
	returnInt[2] = inStream.get();
	returnInt[1] = inStream.get();
	returnInt[0] = inStream.get();
	return out;
}
float getSwappedFloatFromStream(istream& inStream){
	float out;
	char *returnfloat = (char*) & out;
	returnfloat[3] = inStream.get();
	returnfloat[2] = inStream.get();
	returnfloat[1] = inStream.get();
	returnfloat[0] = inStream.get();
	return out;
}
long getSwappedLongFromStream(istream& inStream){
	long out;
	char *returnLong = (char*) & out;
	returnLong[7] = inStream.get();
	returnLong[6] = inStream.get();
	returnLong[5] = inStream.get();
	returnLong[4] = inStream.get();
	returnLong[3] = inStream.get();
	returnLong[2] = inStream.get();
	returnLong[1] = inStream.get();
	returnLong[0] = inStream.get();
	return out;
}
double getSwappedDoubleFromStream(istream& inStream){
	double out;
	char *returnDouble = (char*) & out;
	returnDouble[7] = inStream.get();
	returnDouble[6] = inStream.get();
	returnDouble[5] = inStream.get();
	returnDouble[4] = inStream.get();
	returnDouble[3] = inStream.get();
	returnDouble[2] = inStream.get();
	returnDouble[1] = inStream.get();
	returnDouble[0] = inStream.get();
	return out;
}
string getStringFromStream(istream& inStream, int length){
	char* temp = new char[length];
	for(int i = 0; i < length; i++){
		temp[i] = inStream.get();
	}
	string out(temp);
	delete temp;
	return out;
}


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

char getCharFromTag(TAG_TypeID inTag){
	char out = -1;
	switch (inTag)
	{
	case TAG_End: out = 0;
	break;
	case TAG_Byte: out = 1;
	break;
	case TAG_Short: out = 2;
	break;
	case TAG_Int: out = 3;
	break;
	case TAG_Long: out = 4;
	break;
	case TAG_Float: out = 5;
	break;
	case TAG_Double: out = 6;
	break;
	case TAG_Byte_Array: out = 7;
	break;
	case TAG_String: out = 8;
	break;
	case TAG_List: out = 9;
	break;
	case TAG_Compound: out = 10;
	break;
	case TAG_IntArray: out = 11;
	break;
	}
	return out;
}

void writeSwappedShortToStream(short inShort, ostream& inStream){
	char* lengthChars = (char*) &inShort;
	inStream << (unsigned char)lengthChars[1] << (unsigned char)lengthChars[0];
}
void writeSwappedIntToStream(int inInt, ostream& inStream){
	char* lengthChars = (char*) &inInt;
	inStream << (unsigned char)lengthChars[3] << (unsigned char)lengthChars[2] << (unsigned char)lengthChars[1] <<
			(unsigned char)lengthChars[0];
}
void writeSwappedLongToStream(long inLong, ostream& inStream){
	char* lengthChars = (char*) &inLong;
	inStream << (unsigned char)lengthChars[7] << (unsigned char)lengthChars[6] << (unsigned char)lengthChars[5] <<
			(unsigned char)lengthChars[4] << (unsigned char)lengthChars[3] << (unsigned char)lengthChars[2]<<
			(unsigned char)lengthChars[1] << (unsigned char)lengthChars[0];
}
void writeSwappedFloatToStream(float inFloat, ostream& inStream){
	char* lengthChars = (char*) &inFloat;
	inStream << (unsigned char)lengthChars[3] << (unsigned char)lengthChars[2] << (unsigned char)lengthChars[1] <<
			(unsigned char)lengthChars[0];
}
void writeSwappedDoubleToStream(double inDouble, ostream& inStream){
	char* lengthChars = (char*) &inDouble;
	inStream << (unsigned char)lengthChars[7] << (unsigned char)lengthChars[6] << (unsigned char)lengthChars[5] <<
			(unsigned char)lengthChars[4] << (unsigned char)lengthChars[3] << (unsigned char)lengthChars[2] <<
			(unsigned char)lengthChars[1] << (unsigned char)lengthChars[0];
}








