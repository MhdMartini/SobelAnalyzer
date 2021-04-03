#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "imgIo.h"
#include "imgOp.h"
#include "sobel.h"

int main(){
    // unsigned * shape = get_size(imgSobelPath);
    // unsigned sizeX = shape[0];
    // unsigned sizeY = shape[1];
    imgSobel("test_images/cake.pgm", 55, 1, 256, 256);
    return 0;
}
