#include <stdio.h>
#include "struct.h"



words* creatrStructOfWords (words *word, int *numOfStruct);
void searchSwapWords (words *descriptionOfWord, char** longWORD, char** shortWORD, int numOfStruct);
void replace(char* longWord, char* shortWord);
void addParagraph(words *descriptionOfWord, char **longWORD, char **shortWORD, int numOfStruct);
void freeStruct (words *descriptionOfWord);
void paragraph();


