#ifndef IMGIO_H
#define IMGIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char * readImg(char imgName[]);
void writeImg(char imgName[], unsigned char *image, unsigned sizeX, unsigned sizeY);

#endif
