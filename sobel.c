/*
    Script to
    Author  :   Mohamed Martini
    Date    :   04/01/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imgIo.h"
#include "imgOp.h"

// vertical and horizontal sobel filters
signed sobelV[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
signed sobelH[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

char imgS[] = "output/sobel.pgm";
char imgSB[] = "output/gTruth.pgm";


unsigned char * imgSobel(unsigned char * img, unsigned threshold, unsigned output, unsigned sizeX, unsigned sizeY){
    // take 1d image usigned char array, apply both sobles and add result. Normalize and save the result, then threshold and save.
    // Return normalized sobel image (unsigned char). Only save images if output is not 0
    unsigned sizeXBig = sizeX + 2;  // size of padded image
    unsigned sizeYBig = sizeY + 2;

    unsigned char * imgPadded = imgPad(img, sizeX, sizeY);

    signed * imgConvV = imgConv(imgPadded, sobelV, sizeXBig, sizeYBig);  // result is not padded
    normalize(imgConvV, sizeX, sizeY);

    signed * imgConvH = imgConv(imgPadded, sobelH, sizeXBig, sizeYBig);  // result is not padded
    normalize(imgConvH, sizeX, sizeY);

    // combine, normalize and save image
    signed * imgSobel_ = imgAdd(imgConvV, imgConvH, sizeX, sizeY);  // add vertical and horizontal filters
    unsigned char * imgSobelN = normalize(imgSobel_, sizeX, sizeY);
    if (output){
        // if output, save sobel image, binarize and save binary image
        writeImg(imgS, imgSobelN, sizeX, sizeY);
        unsigned char * imgSobelNBin = imgBin(imgSobelN, threshold, sizeX, sizeY);
        writeImg(imgSB, imgSobelNBin, sizeX, sizeY);
    }

    return imgSobelN;
}
