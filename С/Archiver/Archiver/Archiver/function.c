#define INT_MAX 2147483647
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"



unsigned long checkWord (unsigned long sizeOfWord, char *tempWord) {
    for (unsigned long i=sizeOfWord-1; ; ) {
        if (tempWord[sizeOfWord-1] == ',' || tempWord[sizeOfWord-1] == '.' || tempWord[sizeOfWord-1] == '!' || tempWord[sizeOfWord-1] == '?' || tempWord[sizeOfWord-1] == '"' || tempWord[sizeOfWord-1] == '(' || tempWord[sizeOfWord-1] == ')' || tempWord[sizeOfWord-1] == '<' || tempWord[sizeOfWord-1] == '>') {
            tempWord[sizeOfWord-1]='\0';
            sizeOfWord--;
        }
        else break;
    }
    for (int i=0; i<sizeOfWord; ) {
        if (tempWord[i] == ',' || tempWord[i] == '.' || tempWord[i] == '!' || tempWord[i] == '?' || tempWord[i] == '"' || tempWord[i] == '(' || tempWord[i] == ')' || tempWord[i] == '<' || tempWord[i] == '>') {
            for(int i=0; i<sizeOfWord; i++) {
                tempWord[i]=tempWord[i+1];
            }
            sizeOfWord--;
        }
        else break;
    }
    return sizeOfWord;
}



words* addToStruct (int *numOfStruct, unsigned long sizeOfWord, char tempWord[48], words *descriptionOfWord) {
    int j=0;
    int fl=0;
    for (j=0; j<*numOfStruct; j++) {
        if (strcmp(descriptionOfWord[j].word, tempWord)==0) {
            descriptionOfWord[j].amountOfWord++;
            fl=1;
            break;
        }
    }
    
    if (fl==0) {
        (*numOfStruct)++;
        descriptionOfWord=realloc(descriptionOfWord, (*numOfStruct)*sizeof(words));
        strcpy(descriptionOfWord[j-1].word, tempWord);
        descriptionOfWord[j-1].amountOfWord=1;
        descriptionOfWord[j-1].symbolInWord=sizeOfWord;
    }
    return descriptionOfWord;
}
  


words* creatrStructOfWords (words *descriptionOfWord, int *numOfStruct) {
    FILE *inF=NULL;
    if ((inF = fopen("Text.txt", "r"))== NULL) {
        printf("Error opening Text.txt!\n");
        exit(1);
    }
    char tempWord[47];
    unsigned long sizeOfWord=0;
    descriptionOfWord=calloc(1, sizeof(words));
    while (!feof(inF)) {
        fscanf(inF, "%s", tempWord);
        sizeOfWord=strlen(tempWord);
        sizeOfWord = checkWord (sizeOfWord, tempWord);
        descriptionOfWord = addToStruct (numOfStruct, sizeOfWord, tempWord, descriptionOfWord);
    }
    fclose(inF);
    return descriptionOfWord;
}



void searchSwapWords (words *descriptionOfWord, char** longWORD, char** shortWORD, int numOfStruct) {
    words *longWord = NULL;
    words *shortWord = NULL;
    for (int i = 0; i < numOfStruct; i++) {
        if (!descriptionOfWord[i].usage) {
            if (longWord == NULL || (strlen(descriptionOfWord[i].word) > strlen(longWord->word) && descriptionOfWord[i].amountOfWord > longWord->amountOfWord)) {
                longWord = &descriptionOfWord[i];
                
            }
            if (shortWord == NULL || (strlen(descriptionOfWord[i].word) < strlen(shortWord->word) && descriptionOfWord[i].amountOfWord < shortWord->amountOfWord)) {
                shortWord = &descriptionOfWord[i];
            }
        }
    }
    char tempWord[48];
    int fl=0;
    FILE *library = NULL;
    if ((library = fopen("Library.txt", "a"))== NULL) {
        printf("Error opening Library.txt!\n");
        exit(1);
    }
    while (fscanf(library, "%s", tempWord) != EOF) {
        for (int i = 0; i < numOfStruct; i++) {
            if (strcmp(tempWord, descriptionOfWord[i].word)==0) {
                descriptionOfWord[i].usage=1;
                break;
            }
        }
        if (strcmp(tempWord, longWord->word)==0 || strcmp(tempWord, shortWord->word)==0) {
            fl = 1;
            break;
        }
    }
    
    if (!fl && !longWord->usage && !shortWord->usage) {
        fprintf(library, "%s %s*\n", longWord->word, shortWord->word);
        longWord->usage=1;
        shortWord->usage=1;
        *longWORD=longWord->word;
        *shortWORD=shortWord->word;
    }
    fclose(library);
}



char* readString(FILE* inF) {
    size_t sizeBufer = 1024;
    size_t size = 0;
    char* buffer = malloc(sizeBufer);
    while (fgets(buffer+size, sizeBufer-size, inF)!=NULL) {
        size+=strlen(buffer+size);
        if (buffer[size-1] == '\n')
            break;
        sizeBufer*=2;
        buffer=realloc(buffer, sizeBufer);
    }
    if (size==0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}



int firstSize(words* firstWord, words* secondWord) {
    return strlen(firstWord->word)*firstWord->amountOfWord + strlen(secondWord->word)*secondWord->amountOfWord;
}



int secondSize(words* firstWord, words* secondWord) {
    return strlen(firstWord->word)*secondWord->amountOfWord + strlen(secondWord->word)*firstWord->amountOfWord + strlen(secondWord->word) + strlen(firstWord->word) +2;
}



int searchLengthOfDictionary(int lengthOfDictionary) {
    FILE* library=NULL;
    if ((library = fopen("Library.txt", "r"))==NULL) {
        printf("Error opening Library.txt!\n");
        exit(1);
    }
    fseek(library, 0, SEEK_END);
    lengthOfDictionary=ftell(library);
    lengthOfDictionary+=5;
    return lengthOfDictionary;
}

void replace(char* longWORD, char* shortWORD) {
    int lengthOfDictionary=0;
    char* string=NULL;
    FILE* inF=NULL;
    if ((inF = fopen("Text.txt", "r"))==NULL) {
        printf("Error opening Text.txt!\n");
        exit(1);
    }
    FILE* outF=NULL;
    if ((outF = fopen("ArchivedText.txt", "w+"))==NULL) {
        printf("Error opening ArchivedText.txt!\n");
        exit(1);
    }
    char* secondString=readString(inF);
    while (secondString!=NULL) {
        string=secondString;
        char *words=strtok(string, " \n");
        while(words!=NULL) {
            if (strcmp(words, longWORD)==0)
                fprintf(outF, "%s*", shortWORD);
            else
                fprintf(outF, "%s", words);
            words = strtok(NULL, " \n");
            if (words!=NULL)
                fprintf(outF, " ");
        }
        secondString=readString(inF);
        if (secondString!=NULL)
            fprintf(outF, "\n");
        free(string);
    }
    fclose(inF);
    fclose(outF);
    int size = secondSize(longWORD, shortWORD);
    int oldSize = firstSize(longWORD, shortWORD);
//    lengthOfDictionary=searchLengthOfDictionary(lengthOfDictionary);
//    size+=lengthOfDictionary;
    if (size<oldSize) {
        remove("Text.txt");
        rename("ArchivedText.txt", "Text.txt");
    }
    else
        remove("ArchivedText.txt");
}



void paragraph() {
    char buffer[100];
    FILE* outF=fopen("Text.txt", "a");
    if (outF==NULL) {
        printf("Error opening Text.txt\n");
        exit(1);
    }
    FILE* library=fopen("Library.txt", "r");
    if (library==NULL) {
        printf("Error opening Library.txt\n");
        exit(1);
    }
    fprintf(outF, " *!* ");
    while (fscanf(library, "%s", buffer) != EOF)
        fprintf(outF, "%s ", buffer);
    fclose(outF);
    remove("Library.txt");
    fclose(library);
}



void addParagraph(words *descriptionOfWord, char **longWORD, char **shortWORD, int numOfStruct) {
    while (1) {
        int oldSize = firstSize(*longWORD, *shortWORD);
        searchSwapWords(descriptionOfWord, &(*longWORD), &(*shortWORD), numOfStruct);
        replace(*longWORD, *shortWORD);
        int size = secondSize(*longWORD, *shortWORD);
        if (size>=oldSize) {
            paragraph();
            break;
        }
    }
}

void freeStruct (words *descriptionOfWord) {
    free(descriptionOfWord);
}

