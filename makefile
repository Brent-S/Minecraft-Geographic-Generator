all: run

run: ColourRangeToBlock.o NBTTagNew.o
	g++ `Magick++-config --cxxflags --cppflags` -o run ImageConverter.cpp ColourRangeToBlock.o NBTTagNew.o `Magick++-config --ldflags --libs`

ColourRangeToBlock.o: ColourRangeToBlock.cpp
	g++ -c ColourRangeToBlock.cpp

NBTTagNew.o: NBTTagNew.cpp
	g++ -c NBTTagNew.cpp

clean:
	rm -rf *o run
