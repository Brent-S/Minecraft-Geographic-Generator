

short EndianSwapShort(const short inShort){
   short out;
   char *shortToConvert = (char*) & inShort;
   char *returnShort = (char*) & out;

   returnShort[0] = shortToConvert[1];
   returnShort[1] = shortToConvert[0];

   return out;
}

int EndianSwapInt(const int inInt){
   int out;
   char *intToConvert = (char*) & inInt;
   char *returnInt = (char*) & out;

   returnInt[0] = intToConvert[3];
   returnInt[1] = intToConvert[2];
   returnInt[2] = intToConvert[1];
   returnInt[3] = intToConvert[0];

   return out;
}

long EndianSwapLong(const long inLong){
   long out;
   char *longToConvert = (char*) & inLong;
   char *returnLong = (char*) & out;

   returnLong[0] = longToConvert[7];
   returnLong[1] = longToConvert[6];
   returnLong[2] = longToConvert[5];
   returnLong[3] = longToConvert[4];
   returnLong[4] = longToConvert[3];
   returnLong[5] = longToConvert[2];
   returnLong[6] = longToConvert[1];
   returnLong[7] = longToConvert[0];

   return out;
}

float EndianSwapFloat(const float inFloat){
   float out;
   char *floatToConvert = (char*) & inFloat;
   char *returnFloat = (char*) & out;

   returnFloat[0] = floatToConvert[3];
   returnFloat[1] = floatToConvert[2];
   returnFloat[2] = floatToConvert[1];
   returnFloat[3] = floatToConvert[0];

   return out;
}

double EndianSwapDouble(const double inDouble){
   double out;
   char *doubleToConvert = (char*) & inDouble;
   char *returnDouble = (char*) & out;

   returnDouble[0] = doubleToConvert[7];
   returnDouble[1] = doubleToConvert[6];
   returnDouble[2] = doubleToConvert[5];
   returnDouble[3] = doubleToConvert[4];
   returnDouble[4] = doubleToConvert[3];
   returnDouble[5] = doubleToConvert[2];
   returnDouble[6] = doubleToConvert[1];
   returnDouble[7] = doubleToConvert[0];

   return out;
}
