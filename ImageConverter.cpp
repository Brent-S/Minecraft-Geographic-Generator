#include <iostream>
#include <cstdlib>
#include <Magick++.h>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include "ColourRangeToBlock.h"

using namespace std;
using namespace Magick;

vector<string> split(string str,string sep){
	char* cstr=const_cast<char*>(str.c_str());
	char* current;
	vector<string> out;
	current=strtok(cstr,sep.c_str());
	while(current!=NULL){
		out.push_back(current);
		current=strtok(NULL,sep.c_str());
	}
	return out;
}

vector<ColourRangeToBlock> ReadBlockDefs(){
	string nxtLine;
	vector<ColourRangeToBlock> ranges;

	double MinRed, MaxRed, MinGreen, MaxGreen, MinBlue, MaxBlue;
	int BlockID, DamageValue;

	// Get config from ImageConverter.conf
	ifstream ConfigFile("ImageConverter.conf");

	getline(ConfigFile,nxtLine);
	while (ConfigFile.good())
	{
		if(nxtLine.at(0) == '#'){
			// Do nothing. Line is a comment and should be ignored.
		} else {
			vector<string> BrokenLine = split(nxtLine,"\t");

			vector<string>::iterator n = BrokenLine.begin();
			MinRed = strtod((*n).c_str(),NULL);
			n++;
			MaxRed = strtod((*n).c_str(),NULL);
			n++;
			MinGreen = strtod((*n).c_str(),NULL);
			n++;
			MaxGreen = strtod((*n).c_str(),NULL);
			n++;
			MinBlue = strtod((*n).c_str(),NULL);
			n++;
			MaxBlue = strtod((*n).c_str(),NULL);
			n++;
			BlockID = atoi((*n).c_str());
			n++;
			DamageValue = atoi((*n).c_str());

			ranges.push_back(ColourRangeToBlock(MinRed, MaxRed, MinGreen, MaxGreen, MinBlue, MaxBlue, BlockID, DamageValue));
		}
		getline(ConfigFile,nxtLine);
	}
	return ranges;
}

int main( int /*argc*/, char ** argv) {

	// Reads in colour definitions from ImageConverter.conf and prints to standard out a
	// tab-delimited list of comma-separated (BlockID,DamageValue) pairs, with a newline
	// for each row of pixels.

	InitializeMagick(*argv);
	try {

		vector<ColourRangeToBlock> BlockDefs = ReadBlockDefs();

		// Read test image, just to have some pixels available
		Image picture;
		picture.read("TestImage1.png");

		size_t cols = picture.columns();
		size_t rows = picture.rows();

		const PixelPacket *pixels = picture.getConstPixels(0,0,cols,rows);
		// cout << "Begin image output:\n";
		int i = 0; // pixel iterator
		for(unsigned int r = 0; r < picture.baseRows(); r++){
			for(unsigned int c = 0; c < picture.baseColumns(); c++){
				// cout << (pixels+i)->red << "\t" << (pixels+i)->green << "\t"<< (pixels+i)->blue << "\n";

				// Next, test current pixel against vector BlockDefs, and get BlockID and DamageValue from fist match.
				int BlockID = -1;
				int DamageValue = -1;
				for(size_t j = 0; j < BlockDefs.size(); j++){
					ColourRangeToBlock CurrentBlockDef = BlockDefs.at(j);
					if(CurrentBlockDef.testRGB((pixels+i)->red, (pixels+i)->green, (pixels+i)->blue)){
						BlockID = CurrentBlockDef.getBlockID();
						DamageValue = CurrentBlockDef.getDamageValue();
						break;
					}
				}
				cout << BlockID << "," << DamageValue << "\t";
				i++;
			}
			cout << "\n";
		}


	} catch( Exception &error_ ) {
		cout << "Caught Exception: " << error_.what() << endl;
		return 1;
	} catch( exception &error_ ) {
		cout << "Caught exception: " << error_.what() << endl;
		return 1;
	}

	return 0;
}

