#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

int main( int /*argc*/, char ** argv)
{
	InitializeMagick(*argv);
  try {
    {
      // Read test image, just to have some pixels available
      Image picture;
      picture.read("TestImage1.bmp");
     // picture.write("logo.pnm");

      Pixels view(picture);
      int x = view.x();
      int y = view.y();
      size_t cols = view.columns();
      size_t rows = view.rows();

      const PixelPacket* pixelPacket = view.getConst(x,y,cols,rows);

      for(int r = 0; r < picture.baseRows(); r++){
    	  for(int c = 0; c < picture.baseColumns(); c++){
    		  int i = r + c * picture.baseColumns(); // TODO check this is right with larger image

    		  PixelPacket pixel = pixelPacket[i];
    		  cout << pixel.red << "\t" << pixel.blue << "\t" << pixel.green << "\n";
    	  }
      }

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
