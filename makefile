
sobel: SobelAnalyzer.o imageIo.o imgOp.o
	gcc SobelAnalyzer.o imgIo.o imgOp.o -o SobelAnalyzer

SobelAnalyzer.o: SobelAnalyzer.c
	gcc -c SobelAnalyzer.c

imageIo.o: imgIo.c imgIo.h
	gcc -c imgIo.c

imgOp.o: imgOp.c imgOp.h
    gcc -c imgOp.c

clean:
	rm *.o
