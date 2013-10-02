#include <iostream>
#include <cstdlib>
#include <Magick++.h>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include "ColourRangeToBlock.h"
#include "NBTTagNew.h"

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
		if(nxtLine.compare(0, 6, "block=") == 0) {
			vector<string> BrokenLine = split(nxtLine.substr(6),"\t");

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
		} else {
			//Do nothing.  Line is not a block definition.
		}
		getline(ConfigFile,nxtLine);
	}
	ConfigFile.close();
	return ranges;
}

Image ReadInputImage(){
	Image output;
	ifstream ConfigFile("ImageConverter.conf");
	string nxtLine;
	getline(ConfigFile,nxtLine);
	while (ConfigFile.good())
	{
		if(nxtLine.compare(0, 6, "image=") == 0) {
			output.read(nxtLine.substr(6));
			break;
		} else {
			// Do nothing. Line is not an image input.
		}
		getline(ConfigFile,nxtLine);
	}
	ConfigFile.close();
	return output;
}

double ReadScale(){
	double output = 1;
	ifstream ConfigFile("ImageConverter.conf");
	string nxtLine;
	getline(ConfigFile,nxtLine);
	while (ConfigFile.good())
	{
		if(nxtLine.compare(0, 6, "scale=") == 0) {
			output=strtod((nxtLine.substr(6)).c_str(),NULL);
			break;
		} else {
			// Do nothing. Line is not a scale definition.
		}
		getline(ConfigFile,nxtLine);
	}
	ConfigFile.close();
	return output;
}

int DoPictureStuff() {

	// Reads in colour definitions from ImageConverter.conf and prints to standard out a
	// tab-delimited list of comma-separated (BlockID,DamageValue) pairs, with a newline
	// for each row of pixels.

	InitializeMagick(NULL);
	try {
		vector<ColourRangeToBlock> BlockDefs = ReadBlockDefs();
		Image picture = ReadInputImage();
		double scale = ReadScale();

		size_t cols = picture.columns();
		size_t rows = picture.rows();

		if(scale != 1) {
			picture.modifyImage();
			int NewCols = cols / ((int)scale); // width
			int NewRows = rows / ((int)scale); // height
			picture.resize(Geometry(NewCols,NewRows));
			cols = picture.columns();
			rows = picture.rows();
			picture.write("Image as used.png");
		}

		const PixelPacket *pixels = picture.getConstPixels(0,0,cols,rows);
		// cout << "Begin image output:\n";
		int i = 0; // pixel iterator
		for(unsigned int r = 0; r < rows; r++){
			for(unsigned int c = 0; c < cols; c++){
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


int main() {
	cout << "Enter 1 to do image stuff, or 2 to read test nbt file:\n";
	int inputNum;
	cin >> inputNum;

	if(inputNum == 1){
		return DoPictureStuff();
	} else {
		cout << "Opening file...";
		ifstream inFile("hello_world.nbt");
		cout << " Done." <<"\n" << "Constructing Tags...";
		cout.flush();
		NBTTag rootTag (inFile);
		inFile.close();
		cout <<"Done.\n \n" << rootTag.getDisplayString();
		cout.flush();

		cout << "Writing file out...";
		cout.flush();
		stringstream tempStream;
		rootTag.getStorageBytes(tempStream);
		ofstream outFile("NBTout.nbt");
		outFile << tempStream.rdbuf();
		outFile.close();
		cout << "Done." << endl << endl;

		cout << "Opening file...";
		ifstream inFile2("NBTout.nbt");
		cout << " Done." <<"\n" << "Constructing Tags...";
		cout.flush();
		NBTTag rootTag2 (inFile2);
		inFile.close();
		cout <<"Done.\n \n" << rootTag2.getDisplayString();
		cout.flush();
	}
	cout << "Program execution completed successfully." << endl;
	return 0;
}

