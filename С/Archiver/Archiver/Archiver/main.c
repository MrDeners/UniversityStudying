#include "function.h"



int main() {
    int numOfStruct = 1;
    words *descriptionOfWord = NULL;
    char *longWORD = NULL;
    char *shortWORD = NULL;
    descriptionOfWord = creatrStructOfWords(descriptionOfWord, &numOfStruct);
    searchSwapWords (descriptionOfWord, &longWORD, &shortWORD, numOfStruct);
    replace(longWORD, shortWORD);
    addParagraph(descriptionOfWord, &longWORD, &shortWORD, numOfStruct);
    freeStruct(descriptionOfWord);
    return 0;
}
