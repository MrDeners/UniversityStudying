#include "function.h"


void menu(BMPFile *image) {
    int operation=0;
    printf("\n|------------------------------------------------------|\n");
    printf("Operations:\n");
    printf("1: Converting an Image to Negative\n");
    printf("2: Converting an image to Black and White\n");
    printf("3: Perform median filtering\n");
    printf("4: Perform gamma correction\n");
    printf("5: Close program\n");
    printf("\n");
    printf("Your choice: ");
    while(!scanf("%d", &operation) || operation<1 || operation>5) {
        printf("Pleas, choice existing operation (1, 2, 3, 4 or 5).\n");
        printf("Your choice: ");
        rewind(stdin);
    }
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    if (operation == 5) {
        printf("\n");
        freeStruct(image);
        return;
    }
    choiceOperation(image, operation);
    freeStruct(image);
    image = calloc(1, sizeof(BMPFile));
    menu(image);
}
