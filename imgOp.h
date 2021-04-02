#ifndef IMGOP_H
#define IMGOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned * get_size(char imgName[]);
unsigned * get_coords(unsigned index, unsigned sizeX);
unsigned get_index(unsigned i, unsigned j, unsigned sizeX);
unsigned char * imgPad(unsigned char *img, unsigned sizeX, unsigned sizeY);
signed* imgConv(unsigned char *img, signed filter[9], unsigned sizeX, unsigned sizeY);
unsigned char * normalize(signed * imgConv, unsigned sizeX, unsigned sizeY);
signed * imgAdd(signed * img1, signed * img2, unsigned sizeX, unsigned sizeY);
#endif
