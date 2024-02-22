#include "function.h"


int main() {
    char tempWord[100];
    int amountOfWord=0;
    char** words = NULL;
    words=prepareToProcessing (tempWord, &amountOfWord, words);
    processingFile();
    return 0;
}
