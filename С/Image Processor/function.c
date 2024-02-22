#include "function.h"


void choiceOperation(BMPFile *image, int operation) {
    switch(operation) {
        case 1: conversionToNegative(image);
            break;
        case 2: convertToBlackAndWhite(image);
            break;
        case 3: medianFilter(image);
            break;
        case 4: gammaCorrection(image);
            break;
    }
}

char* choiceFile(char *nameOfFile) {
    int symbol = 0;
    printf ("Please, enter the name of the file, that you want to process: ");
    while ((symbol = getchar()) != '\n');
    fgets(nameOfFile, 255, stdin);
    if (strstr(nameOfFile, ".bmp") == NULL) {
        printf ("This file is not suitable for processing by the program\n");
        return NULL;
    }
    nameOfFile[strcspn(nameOfFile, "\n")] = '\0';
    return nameOfFile;
}

BMPFile* inputImage(BMPFile *image, char *nameOfFile) {
    FILE *file = fopen(nameOfFile, "rb");
    if (file == NULL) {
        printf("Error opening %s!\n", nameOfFile);
        return image;
    }
    fread(&image->BMPFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    
    fread(&image->BMPInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    
    if (image->BMPInfoHeader.biBitCount != 24) {
        printf ("This file is not suitable for processing by the program\n");
        return NULL;
    }
    image->pixels=malloc(image->BMPInfoHeader.biHeight * image->BMPInfoHeader.biWidth * 3);
    fseek(file, image->BMPFileHeader.bfOffBits, SEEK_SET);
    fread(image->pixels, 3 * image->BMPInfoHeader.biSizeImage, 1, file);
    
    
    fclose(file);
    return image;
}

void saveImage(BMPFile *image, char *nameOfFile) {
    printf ("Please, enter the name of the seved file, that you want to process: ");
    scanf("%s", nameOfFile);
    if (strstr(nameOfFile, ".bmp") == NULL) {
        printf ("The file format is not correct\n");
        return;
    }
    nameOfFile[strcspn(nameOfFile, "\n")] = '\0';
    FILE *file = fopen(nameOfFile, "wb");
    if (!file) {
        printf("Error opening %s!\n", nameOfFile);
        return;
    }
    fwrite(&image->BMPFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fwrite(&image->BMPInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    fseek(file, image->BMPFileHeader.bfOffBits, SEEK_SET);
    fwrite(image->pixels, sizeof(char), image->BMPInfoHeader.biSizeImage, file);
    fclose(file);
    free(nameOfFile);
}


void conversionToNegative (BMPFile *image) {
    char *nameOfFile = malloc(256 * sizeof(char));
    nameOfFile = choiceFile(nameOfFile);
    if (nameOfFile == NULL)
        return;
    image = inputImage(image, nameOfFile);
    if (image == NULL)
        return;
    int height = image->BMPInfoHeader.biHeight;
    int width = image->BMPInfoHeader.biWidth;
    int rowSize = ((width * 3 + 3) / 4) * 4;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * rowSize + x * 3;
            image->pixels[index] = 255 - image->pixels[index];
            image->pixels[index + 1] = 255 - image->pixels[index + 1];
            image->pixels[index + 2] = 255 - image->pixels[index + 2];
        }
    }
    printf("\n");
    saveImage(image, nameOfFile);
}

void convertToBlackAndWhite(BMPFile *image) {
    char *nameOfFile = malloc(256 * sizeof(char));
    nameOfFile = choiceFile(nameOfFile);
    if (nameOfFile == NULL)
        return;
    image = inputImage(image, nameOfFile);
    if (image == NULL)
        return;
    int height = image->BMPInfoHeader.biHeight;
    int width = image->BMPInfoHeader.biWidth;
    int rowSize = ((width * 3 + 3) / 4) * 4;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * rowSize + x * 3;
            unsigned char blue = image->pixels[index];
            unsigned char green = image->pixels[index + 1];
            unsigned char red = image->pixels[index + 2];
            
            unsigned char brightness = round(0.299 * red + 0.587 * green + 0.114 * blue);

            image->pixels[index] = brightness;
            image->pixels[index + 1] = brightness;
            image->pixels[index + 2] = brightness;
        }
    }
    printf("\n");
    saveImage(image, nameOfFile);
}

void inputWindowSize (int *windowSize) {
    printf("Pleas, input level of smoothing: ");
    while(!scanf("%d", windowSize)) {
        printf("ERROR: Input number  ->  ");
        rewind(stdin);
    }
}

int compare(const void *a, const void *b) {
    return (*(unsigned char*)a - *(unsigned char*)b);
}

void medianFilter(BMPFile *image) {
    int windowSize = 0;
    char *nameOfFile = malloc(256 * sizeof(char));
    nameOfFile = choiceFile(nameOfFile);
    if (nameOfFile == NULL)
        return;
    inputWindowSize(&windowSize);
    image = inputImage(image, nameOfFile);
    if (image == NULL)
        return;
    int height = image->BMPInfoHeader.biHeight;
    int width = image->BMPInfoHeader.biWidth;
    int rowSize = ((width * 3 + 3) / 4) * 4;
    int halfWindow = windowSize / 2;
    char *newPixels = calloc(image->BMPInfoHeader.biSizeImage, sizeof(char));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * rowSize + x * 3;

            unsigned char windowR[windowSize * windowSize];
            unsigned char windowG[windowSize * windowSize];
            unsigned char windowB[windowSize * windowSize];
            int count = 0;

            for (int i = -halfWindow; i <= halfWindow; i++) {
                for (int j = -halfWindow; j <= halfWindow; j++) {
                    int newY = y + i;
                    int newX = x + j;
                    if (newY >= 0 && newY < height && newX >= 0 && newX < width) {
                        int newIndex = newY * rowSize + newX * 3;
                        windowR[count] = image->pixels[newIndex];
                        windowG[count] = image->pixels[newIndex + 1];
                        windowB[count] = image->pixels[newIndex + 2];
                        count++;
                    }
                }
            }
            qsort(windowR, count, sizeof(unsigned char), compare);
            qsort(windowG, count, sizeof(unsigned char), compare);
            qsort(windowB, count, sizeof(unsigned char), compare);
            newPixels[index] = windowR[count / 2];
            newPixels[index + 1] = windowG[count / 2];
            newPixels[index + 2] = windowB[count / 2];
        }
    }
    free(image->pixels);
    image->pixels = newPixels;
    printf("\n");
    saveImage(image, nameOfFile);
}

void inputGamma (float *gammaR, float *gammaG, float *gammaB) {
    printf("Pleas, input level of gamma RED (0.1 - 5): ");
    while(!scanf("%f", gammaR)) {
        printf("ERROR: Input number  ->  ");
        rewind(stdin);
    }
    printf("Pleas, input level of gamma GREEN (0.1 - 5): ");
    while(!scanf("%f", gammaG)){
        printf("ERROR: Input number  ->  ");
        rewind(stdin);
    }
    printf("Pleas, input level of gamma BLUE (0.1 - 5): ");
    while(!scanf("%f", gammaB)) {
        printf("ERROR: Input number  ->  ");
        rewind(stdin);
    }
}

void gammaCorrection(BMPFile *image) {
    float gammaR = 0;
    float gammaG = 0;
    float gammaB = 0;
    char *nameOfFile = malloc(256 * sizeof(char));
    nameOfFile = choiceFile(nameOfFile);
    if (nameOfFile == NULL)
        return;
    inputGamma(&gammaR, &gammaG, &gammaB);
    image = inputImage(image, nameOfFile);
    if (image == NULL)
        return;
    int height = image->BMPInfoHeader.biHeight;
    int width = image->BMPInfoHeader.biWidth;
    int rowSize = ((width * 3 + 3) / 4) * 4;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * rowSize + x * 3;
            image->pixels[index] = pow(image->pixels[index] / 255.0, gammaB) * 255;
            image->pixels[index + 1] = pow(image->pixels[index + 1] / 255.0, gammaG) * 255;
            image->pixels[index + 2] = pow(image->pixels[index + 2] / 255.0, gammaR) * 255;
        }
    }
    printf("\n");
    saveImage(image, nameOfFile);
}


void freeStruct(BMPFile* image) {
    free(image->pixels);
    free(image);
}


