#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"
#include "menu.h"



void choiceOperation(BMPFile *image, int operation);
char* choiceFile(char *nameOfFile);
BMPFile* inputImage(BMPFile *image, char *nameOfFile);
void conversionToNegative (BMPFile *image);
void convertToBlackAndWhite(BMPFile *image);
void medianFilter(BMPFile *image);
void gammaCorrection(BMPFile *image);
void freeStruct(BMPFile* image);

