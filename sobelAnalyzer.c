
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "imgIo.h"
#include "imgOp.h"
#include "sobel.h"

char * path = "test_images/cake.pgm";
unsigned threshold = 55;  // default value. Optimized for mri

void print_help(){
    // print help menu
    printf("\n********************************** SOBEL ANALYZER **********************************\n\n");
    printf("Please run the sobelAnalyzer as follows:\n\n\t./sobelAnalyzer [--path IMAGE_PATH] [--threshold THRESHOLD]\n");
    printf("\n\tIMAGE_PATH\tPath to the Sobel filter input image. Default: 'test_images/cake.pgm'");
    printf("\n\tTHRESHOLD\tThreshold to binarize the Sobel filtered input image. Default: 55\n");
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

    imgSobel(path, threshold, 0, 256, 256);
}

// int main(){
//     // unsigned * shape = get_size(imgSobelPath);
//     // unsigned sizeX = shape[0];
//     // unsigned sizeY = shape[1];
//     imgSobel("test_images/cake.pgm", 55, 1, 256, 256);
//     return 0;
// }
