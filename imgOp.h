#ifndef IMGOP_H
#define IMGOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned * get_size(char imgName[]);
unsigned * get_coords(unsigned index, unsigned sizeX);
unsigned get_index(unsigned i, unsigned j, unsigned sizeX);
unsigned char * imgPad(unsigned char *img, unsigned sizeX, unsigned sizeY);
unsigned char * imgConv(unsigned char *img, unsigned char *filter, unsigned sizeX, unsigned sizeY);
unsigned char * normalize(signed * imgConv, unsigned sizeX, unsigned sizeY);
#endif
