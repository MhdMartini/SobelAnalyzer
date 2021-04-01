#ifndef IMGPREP_H
#define IMGPREP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcs
unsigned * get_coords(unsigned index, unsigned sizeX);
unsigned get_index(unsigned i, unsigned j, unsigned sizeX);
unsigned char * imgPad(unsigned char *img, unsigned sizeX, unsigned sizeY);

#endif
