#ifndef COLOURRANGETOBLOCK_H_
#define COLOURRANGETOBLOCK_H_

class ColourRangeToBlock {
private:
	double MinRed, MaxRed, MinGreen, MaxGreen, MinBlue, MaxBlue;
	int BlockID, DamageValue;
public:
	ColourRangeToBlock(double inMinRed, double inMaxRed, double inMinGreen, double inMaxGreen,
			double inMinBlue, double inMaxBlue, int inBlockID, int inDamageValue);
	double getMinRed();
	double getMaxRed();
	double getMinGreen();
	double getMaxGreen();
	double getMinBlue();
	double getMaxBlue();
	int getBlockID();
	int getDamageValue();
	bool testRGB(int R, int G, int B);
};

#endif /* COLOURRANGETOBLOCK_H_ */
