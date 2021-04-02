sobel: sobel.o imageIo.o imgOp.o
	gcc sobel.o imgIo.o imgOp.o -o sobel

sobel.o: sobel.c
	gcc -c sobel.c

imageIo.o: imgIo.c imgIo.h
	gcc -c imgIo.c

imgOp.o: imgOp.c imgOp.h
	gcc -c imgOp.c

clean:
	rm *.o
