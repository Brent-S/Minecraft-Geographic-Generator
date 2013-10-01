FLAGS= -Wall
MAGICK1=`Magick++-config --cxxflags --cppflags`
MAGICK2=`Magick++-config --ldflags --libs`


all: run

run: ColourRangeToBlock.o NBTTagNew.o ImageConverter.cpp
	g++ $(MAGICK1) $(FLAGS) -o run ImageConverter.cpp ColourRangeToBlock.o NBTTagNew.o $(MAGICK2)
	printf "Compilation completed succesfully. \n \n \n"

ColourRangeToBlock.o: ColourRangeToBlock.cpp
	g++ -c $(FLAGS) ColourRangeToBlock.cpp

NBTTagNew.o: NBTTagNew.cpp
	g++ -c $(FLAGS) NBTTagNew.cpp

clean:
	rm -rf *o run
