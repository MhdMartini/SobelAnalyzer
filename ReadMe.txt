Functions:
    -  take in an image path and read that image into 1D array. CHECK
    -  take in the 1D array and return a padded 1D
        -  create a bigger array (x,y => x+2, y+2)
        -  copy values to big array:
            -  0's where?
                -  j = 0
                -  j = sizeX + 2
                -  i = 0
                -  i = sizeY + 2
    -  take in a padded 1D array and 1D filter and return the filtered 1D array


Get index from i and j:

    for i in range(sizeY):
        for j in range(sizeX):
            print(sizeX*i + j)


Get i and j from index:

    j, i = index % sizeX, index / sizeX
