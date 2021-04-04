    This executable analyzes the performance of the Sobel Edge Detection Filter on noisy image and noisy images after smoothing.
An input image is read and filtered with the Sobel filter by combining the results of vertical and horizontal Sobel filters.
A ground truth image is then obtained by staticly thresholding the filtered image. Threshold can be changed from command line arguments.
    The ground truth image is then used to test the performance of the Sobel filter on noisy versions of the input image. Four levels of noise
are applied to the input image (4, 16, 32, 64). For each noise level, the noisy image is Sobel filtered, then the best binarization threshold
is iteratively found and applied to the filtered noisy image. The result is then compared to the ground truth image.
    The executable will output text analzying the Sobel performance. Additionally, you can view the compared images, the Sobel filtered image, and
the ground truth image by setting OUTPUT to 1 in the executable's command line arguments.

Source:
    sobelAnalyzer.c
    sobel.c
    imgOp.c
    imgIo.c

Executable:
    sobelAnalyzer

Build:
    make

Run:
    Get the help menu by calling the executable with the help flag:
        ./sobelAnalyzer --help

    Help menu:

        ****************************************** SOBEL ANALYZER ******************************************

        Please run the sobelAnalyzer as follows:

            ./sobelAnalyzer [--path IMAGE_PATH] [--threshold THRESHOLD] [--output OUTPUT]

            IMAGE_PATH  -str- Path to the Sobel filter input image. Default: 'test_images/cake.pgm'
            THRESHOLD   -unsigned- Threshold to binarize the Sobel filtered input image. Default: 55
            OUTPUT      -bool- 1: Images output. 0: No output. Default: 0
