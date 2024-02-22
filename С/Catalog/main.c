#include "Struct.h"
#include "menu.h"
#include "function.h"

int searchNumOfStruct(int numOfStruct);



int main() {
    int numOfStruct = 0;
    phones *catalog = NULL;
    numOfStruct = searchNumOfStruct(numOfStruct);
    catalog=structCreate(catalog, numOfStruct);
    menu(catalog, numOfStruct);
    structCleaning (catalog, numOfStruct);
    return 0;
}



int searchNumOfStruct(int numOfStruct) {
    printf("Input amount of struct: ");
    while(!scanf("%d", &numOfStruct)) {
        printf("Pleas, input amount of struct: ");
        rewind(stdin);
    }
    return numOfStruct;
}
