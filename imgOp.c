/*
    Script to get image shape and perform image operations necessary for spatial 3x3 filter applications
    Author  :   Mohamed Martini
    Date    :   04/03/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) (a < b) ? b : a
#define MIN(a, b) (a < b) ? a : b

unsigned * get_size(char imgName[]){
    // take in image name in return its size as [sizeX, sizeY]
    unsigned sizeX;  // width
    unsigned sizeY;  // height
    unsigned levels;
    unsigned *size;
    size=(unsigned *) malloc(2);

    FILE *iFile = fopen(imgName,"r");
    if(iFile==0) return 0;
    if (3 != fscanf(iFile, "P5 %d %d %d ", &sizeX, &sizeY, &levels)) return 0;
    size[0] = sizeX;
    size[1] = sizeY;

    return size;
}

unsigned * get_coords(unsigned index, unsigned sizeX){
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
    unsigned * coords;
    bool cond1, cond2, cond3, cond4;  // conditions at which we pad
    for (unsigned indexBig = 0; indexBig < sizeXBig * sizeYBig; indexBig ++){
        coords = get_coords(indexBig, sizeXBig);
        i = coords[0];  // row
        j = coords[1];  // col
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
    return paddedImg;
}

signed * imgConv(unsigned char *imgPadded, signed filter[9], unsigned sizeXBig, unsigned sizeYBig){
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
    unsigned * coords;
    bool cond1, cond2, cond3, cond4;  // conditions at which we pad
    signed filterVal;  // to hold colvolutuion result
    unsigned center, up, down, left, right, upRight, upLeft, downRight, downLeft;

    for (unsigned indexBig = 0; indexBig < sizeXBig * sizeYBig; indexBig ++){
        coords = get_coords(indexBig, sizeXBig);
        i = coords[0];  // row
        j = coords[1];  // col

        cond1 = (i == 0);
        cond2 = (i == (sizeYBig - 1));
        cond3 = (j == 0);
        cond4 = (j == (sizeXBig - 1));
        if (cond1 || cond2 || cond3 || cond4){
            continue;
        }

        // get indecies of the 3x3 around the pixel to be filtered
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
        imgConv[i] *= (imgConv[i] < 0) ? -1 : 1;  // modify input
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

signed * imgAdd(signed * img1, signed * img2, unsigned sizeX, unsigned sizeY){
    // add filtered images
    signed * result;
    result = (signed*) calloc(sizeof(signed), sizeX * sizeY);
    for (unsigned index = 0; index < sizeX * sizeY; index++){
        result[index] = img1[index] + img2[index];
    }
    return result;
}

unsigned char * imgBin(unsigned char * img, unsigned threshold, unsigned sizeX, unsigned sizeY){
    unsigned char * result;
    result = (unsigned char*) calloc(sizeof(unsigned char), sizeX * sizeY);
    for (unsigned i = 0; i < sizeX * sizeY; i++){
        result[i] = 255 * (img[i] > threshold);
    }
    return result;
}

unsigned char * imgNoise(unsigned char img[], unsigned level, unsigned sizeX, unsigned sizeY){
    // get an unsigned char image and return unsigned char image with noise
    unsigned char * result;
    result = (unsigned char*) calloc(sizeof(unsigned char), sizeX * sizeY);

    for (unsigned i = 0; i < sizeX * sizeY; i++){
        float randVal = (float) rand();
        randVal = ((2 * randVal - RAND_MAX)/RAND_MAX) * level;
        randVal += img[i];
        randVal = MAX(0, randVal);
        randVal = MIN(randVal, 255);
        result[i] = (unsigned) randVal;
    }
    return result;
}

float imgsComp(unsigned char gTruth[], unsigned char img[], unsigned sizeX, unsigned sizeY){
    // return a percentage score for how many pixels match between two images
    float acc = 0;
    float unmBlack = 0;
    for (unsigned i = 0; i < sizeX * sizeY; i++){
        if (gTruth[i] == 0){
            unmBlack += 1;
            acc += (gTruth[i] == img[i]) ? 0 : -1;
            continue;
        }
        else {
            acc += (gTruth[i] == img[i]) ? 1 : 0;
        }
    }
    return acc / (sizeX * sizeY - unmBlack) * 100;
}
