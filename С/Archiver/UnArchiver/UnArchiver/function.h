#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace(char* firstWord, char* secondWord);
int searchParagraph(FILE* text, char* buffer);
int searchAmountOfWord(FILE* inF, char* buffer);
char** memory(int amountOfWord);
void copyBufferToArray(FILE* text, char** words, char* buffer);
void processingFile();
char** prepareToProcessing (char *tempWord, int *amountOfWord, char** words);
