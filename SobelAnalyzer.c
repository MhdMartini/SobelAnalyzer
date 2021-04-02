/*
    Script to
    Author  :   Mohamed Martini
    Date    :   04/01/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "imgIo.h"
#include "imgOp.h"

// vertical and horizontal sobel filters
signed sobelV[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
signed sobelH[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

unsigned NUM_ARGS = 3;  // number if command line arguments

void print_help(){
    // print help menu
    printf("\n********************************** SOBEL ANALYZER **********************************\n\n");
    printf("Please run the SobelAnalyzer as follows:\n\n\t./SobelAnalyzer --image_sobel IMAGE_PATH\n");
    printf("\n\t<>\t<>");
}

int main(int argc, char *argv[]){
    if (argc != NUM_ARGS){
        print_help();
        return 0;
    }
    else if ((argc == 2) && !(strcmp(argv[1], "--help"))){
        print_help();
        return 0;
    }

    // initialize default arguments
    char * imgSobelPath;


    // parse input arguments
    for (unsigned i = 1; i < argc; i += 2){
        if (strcmp(argv[i], "--image_sobel") == 0){
            imgSobelPath = argv[i + 1];
        }
    }

    // read image pad, apply soble, normalize it, then save resulting image
    unsigned char * img = readImg(imgSobelPath);
    unsigned * shape = get_size(imgSobelPath);
    unsigned sizeX = shape[0];
    unsigned sizeY = shape[1];
    unsigned sizeXBig = sizeX + 2;  // size of padded image
    unsigned sizeYBig = sizeY + 2;

    // unsigned char * imgPadded = imgPad(img, sizeXBig, sizeYBig);

    unsigned char * imgPadded = imgPad(img, sizeXBig, sizeYBig);

    signed * imgConvV = imgConv(imgPadded, sobelV, sizeXBig, sizeYBig);  // result is not padded
    unsigned char * imgConvVN = normalize(imgConvV, sizeX, sizeY);

    writeImg("V.pgm", imgConvVN, sizeX, sizeY);

    signed * imgConvH = imgConv(imgPadded, sobelH, sizeXBig, sizeYBig);  // result is not padded
    unsigned char * imgConvHN = normalize(imgConvH, sizeX, sizeY);

    writeImg("H.pgm", imgConvHN, sizeX, sizeY);

    unsigned char * imgSobel = imgAdd(imgConvVN, imgConvHN, sizeX, sizeY);

    writeImg("test.pgm", imgSobel, sizeX, sizeY);

    return 0;
}
