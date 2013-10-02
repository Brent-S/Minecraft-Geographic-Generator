
#include "zlib.h"
#include <iostream>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

using namespace std;

void decompressFileIntoStream(string filename, istream& inStream);
int def(FILE *source, FILE *dest, int level);
int inf(FILE *source, FILE *dest);
