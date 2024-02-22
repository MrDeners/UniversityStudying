#include "Struct.h"
#include "menu.h"
#include "function.h"


#include <stdlib.h>


void menu(phones *catalog, int numOfStruct) {
    int operation=0;
    printf("\n|------------------------------------------------------|\n");
    printf("Operations:\n");
    printf("1: Output catalog\n");
    printf("2: Delet an object in the catalog\n");
    printf("3: Sort catalog by parameter\n");
    printf("4: Come back a start position\n");
    printf("5: Finish job with catalog\n");
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
        return;
    }
    numOfStruct=choiceOperation(catalog, operation, numOfStruct);
    menu(catalog, numOfStruct);
}
