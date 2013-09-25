#include "ColourRangeToBlock.h"
using namespace std;

ColourRangeToBlock::ColourRangeToBlock(double inMinRed, double inMaxRed, double inMinGreen, double inMaxGreen,
			double inMinBlue, double inMaxBlue, int inBlockID, int inDamageValue) {
	MinRed = inMinRed;
	MaxRed = inMaxRed;
	MinGreen = inMinGreen;
	MaxGreen = inMaxGreen;
	MinBlue = inMinBlue;
	MaxBlue = inMaxBlue;
	BlockID = inBlockID;
	DamageValue = inDamageValue;
}

double ColourRangeToBlock::getMinRed(){
	return MinRed;
}
double ColourRangeToBlock::getMaxRed(){
	return MaxRed;
}
double ColourRangeToBlock::getMinGreen(){
	return MinGreen;
}
double ColourRangeToBlock::getMaxGreen(){
	return MaxGreen;
}
double ColourRangeToBlock::getMinBlue(){
	return MinBlue;
}
double ColourRangeToBlock::getMaxBlue(){
	return MaxBlue;
}
int ColourRangeToBlock::getBlockID(){
	return BlockID;
}
int ColourRangeToBlock::getDamageValue(){
	return DamageValue;
}

bool ColourRangeToBlock::testRGB(int R, int G, int B){
	return (R >= MinRed) && (R <= MaxRed) && (G >= MinGreen) && (G <= MaxGreen) && (B >= MinBlue) && (B <= MaxBlue);
}
