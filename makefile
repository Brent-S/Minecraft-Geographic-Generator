FLAGS= -Wall
MAGICK1=`Magick++-config --cxxflags --cppflags`
MAGICK2=`Magick++-config --ldflags --libs`


all: run

run: ColourRangeToBlock.o NBTTagNew.o ImageConverter.cpp gzipReader.o
	g++ $(MAGICK1) $(FLAGS) -o run ImageConverter.cpp ColourRangeToBlock.o NBTTagNew.o gzipReader.o $(MAGICK2)
	printf "Compilation completed succesfully. \n \n"

ColourRangeToBlock.o: ColourRangeToBlock.cpp ColourRangeToBlock.h
	g++ -c $(FLAGS) ColourRangeToBlock.cpp

NBTTagNew.o: NBTTagNew.cpp NBTTagNew.h EndianSwaps.h
	g++ -c $(FLAGS) NBTTagNew.cpp

gzipReader.o: gzipReader.h gzipReader.cpp
	g++ -c $(FLAGS) gzipReader.cpp



clean:
	rm -rf *o run
