#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned * get_coords(unsigned index, unsigned sizeX)
{
    // take an array's index and width and return the i, j coordinates (row, col)
    unsigned *coords;
    coords = (unsigned *) malloc(2);
    coords[0] = index / sizeX;
    coords[1] = index % sizeX;
    return coords;
}

unsigned get_index(unsigned i, unsigned j, unsigned sizeX){
    // take in row and col and width, and return the linear index
    return sizeX * i + j;
}

unsigned char * imgPad(unsigned char *img, unsigned sizeX, unsigned sizeY){
    // pad with two columns and two rows of zeros
    unsigned sizeXNew = sizeX + 2;
    unsigned sizeYNew = sizeY + 2;
    unsigned char * paddedImg;

    paddedImg = (unsigned char*) calloc(sizeof(unsigned char), sizeXNew * sizeYNew);

    // copy the smaller image into the new one
    unsigned oldIndex = 0
    unsigned i, j;
    bool cond1, cond2, cond3, cond4;  // conditions at which we pad
    for (unsigned indexNew = 0; indexNew < sizeXNew * sizeYNew; indexNew ++){
        i = indexNew / sizeXNew;  // row
        j = indexNew % sizeXNew;  // col
        // conditions that indicate we are at the boundary. If at boundery, value is already zero
        // otherwise copy from old array and increment old index
        cond1 = (i == 0);
        cond2 = (i == (sizeYNew - 1));
        cond3 = (j == 0);
        cond4 = (j == (sizeXNew - 1));
        if (cond1 || cond2 || cond3 || cond4){
            continue;
        }
        paddedImg[index] = img[old_index];
        old_index += 1;
    }
}
