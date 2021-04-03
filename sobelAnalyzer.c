
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "imgIo.h"
#include "imgOp.h"
#include "sobel.h"

char * path = "test_images/cake.pgm";
unsigned threshold = 55;  // default value. Optimized for mri
unsigned NOISE[4] = {8, 16, 32, 64};  // levels of noise to be applied
unsigned char * gTruth, * img, * imgSobelNorm, * imgSobelN1, * imgSobelN2, * imgSobelN3, * imgSobelN4;
unsigned * shape;
unsigned sizeX, sizeY;


void print_help(){
    // print help menu
    printf("\n********************************** SOBEL ANALYZER **********************************\n\n");
    printf("Please run the sobelAnalyzer as follows:\n\n\t./sobelAnalyzer [--path IMAGE_PATH] [--threshold THRESHOLD]\n");
    printf("\n\tIMAGE_PATH\tPath to the Sobel filter input image. Default: 'test_images/cake.pgm'");
    printf("\n\tTHRESHOLD\tThreshold to binarize the Sobel filtered input image. Default: 55\n");
}

void analyze(unsigned char * imgNoisy, unsigned level){
    // apply sobel, and find best threshold for binarization

    unsigned char * imgSobelNoisy = imgSobel(imgNoisy, threshold, 0, sizeX, sizeY);
    unsigned char * imgSobelNoisyBin;
    unsigned char * imgSobelNoisyBinBest;
    unsigned threshTemp;
    unsigned threshTempBest = 0;
    float acc;
    float accBest = 0;
    char outName[50];
    for (unsigned threshTemp = 0; threshTemp < 255; threshTemp ++){
        imgSobelNoisyBin = imgBin(imgSobelNoisy, threshTemp, sizeX, sizeY);
        acc = imgsComp(gTruth, imgSobelNoisyBin, sizeX, sizeY);
        if (acc > accBest){
            accBest = acc;
            threshTempBest = threshTemp;
            imgSobelNoisyBinBest = imgSobelNoisyBin;
        }
    }
    printf("Best Accuracy:\t%.2f percent\n", accBest);
    printf("Threshold:\t%u\n", threshTempBest);

    sprintf(outName, "Best_at_%u.pgm", level);
    puts(outName);
    writeImg(outName, imgSobelNoisyBinBest, sizeX, sizeY);  // debug

}

int main(int argc, char *argv[]){
    // parse input arguments
    for (unsigned i = 1; i < argc; i++){
        if (strcmp(argv[i], "--path") == 0){
            path = argv[i + 1];
        }
        else if (strcmp(argv[i], "--threshold") == 0){
            long temp = strtol(argv[i + 1], NULL, 10);
            threshold = (unsigned) temp;
        }
        else if (strcmp(argv[i], "--help") == 0){
            print_help();
            return 0;
        }
    }

    // read image and get its size
    img = readImg(path);
    shape = get_size(path);
    sizeX = shape[0];
    sizeY = shape[1];

    // save ground truth
    imgSobelNorm = imgSobel(img, threshold, 1, sizeX, sizeY);
    gTruth = imgBin(imgSobelNorm, threshold, sizeX, sizeY);

    // apply four levels of noise, and analyze the sobel filter at each level.
    for (unsigned i = 0; i < sizeof(NOISE)/sizeof(NOISE[0]); i++){
        unsigned char * temp = imgNoise(img, NOISE[i], sizeX, sizeY);
        printf("\nAnalyzing the Sobel Filter at noise level '%u'...\n", NOISE[i]);
        analyze(temp, NOISE[i]);
    }


}
