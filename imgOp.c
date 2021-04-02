#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

unsigned char * imgPad(unsigned char *img, unsigned sizeXSmall, unsigned sizeYSmall){
    // pad with two columns and two rows of zeros
    unsigned sizeXBig = sizeXSmall + 2;
    unsigned sizeYBig = sizeYSmall + 2;
    unsigned char * paddedImg;
    paddedImg = (unsigned char*) calloc(sizeof(unsigned char), sizeXBig * sizeYBig);

    // copy the smaller image into the new one
    unsigned indexSmall = 0;
    unsigned i, j;
    bool cond1, cond2, cond3, cond4;  // conditions at which we pad
    for (unsigned indexBig = 0; indexBig < sizeXBig * sizeYBig; indexBig ++){
        i = indexBig / sizeXBig;  // row
        j = indexBig % sizeYBig;  // col
        // conditions that indicate we are at the boundary. If at boundery, value is already zero
        // otherwise copy from old array and increment small index
        cond1 = (i == 0);
        cond2 = (i == (sizeYBig - 1));
        cond3 = (j == 0);
        cond4 = (j == (sizeXBig - 1));
        if (cond1 || cond2 || cond3 || cond4){
            continue;
        }
        paddedImg[indexBig] = img[indexSmall];
        indexSmall += 1;
    }
}

signed * imgConv(unsigned char *imgPadded, signed *filter, unsigned sizeXBig, unsigned sizeYBig){
    // take an a 1D image and a 1D filter and apply the filter as if inputs are two dimentional
    // return filtered image or integers (to be normalized)
    unsigned sizeXSmall = sizeXBig - 2;
    unsigned sizeYSmall = sizeYBig - 2;

    signed * filteredImg;
    filteredImg = (signed*) calloc(sizeof(signed), sizeXSmall * sizeYSmall);


    // get indecies of the 3x3 filter
    unsigned centerF, upF, downF, leftF, rightF, upRightF, upLeftF, downRightF, downLeftF;
    centerF     = get_index(1, 1, 3);
    upF         = get_index(0, 1, 3);
    downF       = get_index(2, 1, 3);
    leftF       = get_index(1, 0, 3);
    rightF      = get_index(1, 2, 3);
    upRightF    = get_index(0, 2, 3);
    upLeftF     = get_index(0, 0, 3);
    downRightF  = get_index(2, 2, 3);
    downLeftF   = get_index(2, 0, 3);

    // convolve
    unsigned indexSmall = 0;
    unsigned i, j;
    bool cond1, cond2, cond3, cond4;  // conditions at which we pad
    signed filterVal;  // to hold colvolutuion result

    for (unsigned indexBig = 0; indexBig < sizeXBig * sizeYBig; indexBig ++){
        i = indexBig / sizeXBig;  // row
        j = indexBig % sizeYBig;  // col

        cond1 = (i == 0);
        cond2 = (i == (sizeYBig - 1));
        cond3 = (j == 0);
        cond4 = (j == (sizeXBig - 1));
        if (cond1 || cond2 || cond3 || cond4){
            continue;
        }

        // get indecies of the 3x3 around the pixel to be filtered
        unsigned center, up, down, left, right, upRight, upLeft, downRight, downLeft;
        center      = get_index(i    , j    , sizeXBig);
        up          = get_index(i - 1, j    , sizeXBig);
        down        = get_index(i + 1, j    , sizeXBig);
        left        = get_index(i    , j - 1, sizeXBig);
        right       = get_index(i    , j + 1, sizeXBig);
        upRight     = get_index(i - 1, j + 1, sizeXBig);
        upLeft      = get_index(i - 1, j - 1, sizeXBig);
        downRight   = get_index(i + 1, j + 1, sizeXBig);
        downLeft    = get_index(i + 1, j - 1, sizeXBig);


        // calculate and populate filtered values
        filterVal = imgPadded[center] * filter[centerF] + imgPadded[up] * filter[upF] + imgPadded[down] * filter[downF] + \
                     imgPadded[left] * filter[leftF] + imgPadded[right] * filter[rightF] + imgPadded[upRight] * filter[upRightF] + \
                     imgPadded[upLeft] * filter[upLeftF] + imgPadded[downRight] * filter[downRightF] + imgPadded[downLeft] * filter[downLeftF];

        filteredImg[indexSmall] = filterVal;
        indexSmall += 1;
    }
    return filteredImg;
}

unsigned char * normalize(signed * imgConv, unsigned sizeX, unsigned sizeY) {
    // take in a 1D signed image and return a 1D unsigned char normalized image
    int min = RAND_MAX;
    int max = -RAND_MAX;
    signed temp;
    unsigned char *imgNorm;  // output 1D array
    imgNorm = (unsigned char*) calloc(sizeof(unsigned char), sizeX * sizeY);
    for (unsigned i = 0; i < sizeX * sizeY; i++){
        // get min and max
        if (imgConv[i] > max){
            max = imgConv[i];
        }
        if (imgConv[i] < min){
            min = imgConv[i];
        }
    }
    // normalize using min and max
    for (unsigned i = 0; i < sizeX * sizeY; i++){
        temp = imgConv[i];
        imgNorm[i] = 255 * (temp - min)/(max - min);
    }
    return imgNorm;
}
