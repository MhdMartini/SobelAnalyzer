sobelAnalyzer:

read image
save ground truth:
    - apply sobel and binarize
apply different levels of noise to original- 4
for each noise level:
    apply soble
    try a range of thresholds, calc accuracy of each, and return the best threshold with its accuracy


functions:
    -  take in a noisy image as 1D array. Apply sobel, binarize, and pass to:
    -  find accuracy: take in a binary image, apply different thresholds and return the best
