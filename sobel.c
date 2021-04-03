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

char imgS[] = "sobel.pgm";
char imgSB[] = "sobel_binary.pgm";

unsigned char * imgSobel(char imgSobelPath[], unsigned threshold, unsigned output, unsigned sizeX, unsigned sizeY){
    // read image path, apply both sobles and add result. Normalize and save the result, then threshold and save.
    // Return normalized sobel image (unsigned char). Only save images if output is not 0
    unsigned char * img = readImg(imgSobelPath);
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

// int main(){
//     return 0;
// }

// unsigned THRESHOLD = 55;  // above: white, below: black
// unsigned NUM_ARGS = 5;  // number if command line arguments

// void print_help(){
//     // print help menu
//     printf("\n********************************** SOBEL ANALYZER **********************************\n\n");
//     printf("Please run the SobelAnalyzer as follows:\n\n\t./SobelAnalyzer --image_sobel IMAGE_PATH\n");
//     printf("\n\tIMAGE_PATH\tPath to the Sobel filter input image\n");
// }

// int main(int argc, char *argv[]){
//     if (argc != NUM_ARGS){
//         print_help();
//         return 0;
//     }
//     else if ((argc == 2) && !(strcmp(argv[1], "--help"))){
//         print_help();
//         return 0;
//     }

//     // parse input arguments
//     char * imgSobelPath;
//     for (unsigned i = 1; i < argc; i += 2){
//         if (strcmp(argv[i], "--path") == 0){
//             imgSobelPath = argv[i + 1];
//         }
//         else if (strcmp(argv[i], "--threshold") == 0){
//             long temp = strtol(argv[i + 1], NULL, 10);
//             THRESHOLD = (unsigned) temp;
//         }
//     }

//     // read image pad, apply both sobles and add result, then normalize and save
//     unsigned char * img = readImg(imgSobelPath);
//     unsigned * shape = get_size(imgSobelPath);
//     unsigned sizeX = shape[0];
//     unsigned sizeY = shape[1];
//     unsigned sizeXBig = sizeX + 2;  // size of padded image
//     unsigned sizeYBig = sizeY + 2;

//     unsigned char * imgPadded = imgPad(img, sizeX, sizeY);

//     signed * imgConvV = imgConv(imgPadded, sobelV, sizeXBig, sizeYBig);  // result is not padded
//     normalize(imgConvV, sizeX, sizeY);

//     signed * imgConvH = imgConv(imgPadded, sobelH, sizeXBig, sizeYBig);  // result is not padded
//     normalize(imgConvH, sizeX, sizeY);

//     // combine, normalize and save image
//     signed * imgSobel = imgAdd(imgConvV, imgConvH, sizeX, sizeY);  // add vertical and horizontal filters
//     unsigned char * imgSobelN = normalize(imgSobel, sizeX, sizeY);
//     writeImg(imgS, imgSobelN, sizeX, sizeY);

//     unsigned char * imgSobelNBin = imgBin(imgSobelN, THRESHOLD, sizeX, sizeY);
//     writeImg(imgSB, imgSobelNBin, sizeX, sizeY);
//     return 0;
// }
