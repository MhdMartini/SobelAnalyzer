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
unsigned thresh= 50;  // if (pixel < 50) or (255 - pixel < 50) turn white otherwise black


unsigned NUM_ARGS = 3;  // number if command line arguments

char imgH[] = "horizontal.pgm";
char imgV[] = "vertical.pgm";
char imgS[] = "sobel.pgm";

void print_help(){
    // print help menu
    printf("\n********************************** SOBEL ANALYZER **********************************\n\n");
    printf("Please run the SobelAnalyzer as follows:\n\n\t./SobelAnalyzer --image_sobel IMAGE_PATH\n");
    printf("\n\t--image_sobel\tPath to the Sobel filter input image\n");
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

    // parse input arguments
    char * imgSobelPath;
    for (unsigned i = 1; i < argc; i += 2){
        if (strcmp(argv[i], "--image_sobel") == 0){
            imgSobelPath = argv[i + 1];
        }
    }

    // read image pad, apply both sobles and add result, then normalize and save
    unsigned char * img = readImg(imgSobelPath);
    unsigned * shape = get_size(imgSobelPath);
    unsigned sizeX = shape[0];
    unsigned sizeY = shape[1];
    unsigned sizeXBig = sizeX + 2;  // size of padded image
    unsigned sizeYBig = sizeY + 2;

    unsigned char * imgPadded = imgPad(img, sizeX, sizeY);
    writeImg("imgPadded.pgm", imgPadded, sizeXBig, sizeYBig);  // debugging

    signed * imgConvV = imgConv(imgPadded, sobelV, sizeXBig, sizeYBig);  // result is not padded
    unsigned char * imgConvVN = normalize(imgConvV, sizeX, sizeY);  // debugging
    writeImg(imgV, imgConvVN, sizeX, sizeY);  // debugging

    signed * imgConvH = imgConv(imgPadded, sobelH, sizeXBig, sizeYBig);  // result is not padded
    unsigned char * imgConvHN = normalize(imgConvH, sizeX, sizeY);  // debugging
    writeImg(imgH, imgConvHN, sizeX, sizeY);  // debugging


    // combine, normalize and save image
    signed * imgSobel = imgAdd(imgConvV, imgConvH, sizeX, sizeY);  // add vertical and horizontal filters
    unsigned char * imgSobelN = normalize(imgSobel, sizeX, sizeY);
    writeImg(imgS, imgSobelN, sizeX, sizeY);

    return 0;
}
