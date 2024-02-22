#include "function.h"

char* checkWord (unsigned long sizeOfWord, char *tempWord) {
    for (unsigned long i=sizeOfWord-1; ; ) {
        if (tempWord[sizeOfWord-1] == '*') {
            tempWord[sizeOfWord-1]='\0';
            sizeOfWord--;
        }
        else break;
    }
    return tempWord;
}


void replace(char* firstWord, char* secondWord) {
    FILE *inF=NULL;
    if ((inF = fopen("Text.txt", "r"))== NULL) {
        printf("Error opening Text.txt!\n");
        exit(1);
    }
    FILE *outF=NULL;
    if ((outF = fopen("ArchivedText.txt", "w"))== NULL) {
        printf("Error opening ArchivedText.txt!\n");
        exit(1);
    }
    size_t bufferSize=1024;
    char* tempString=malloc(bufferSize);
    while (fgets(tempString, bufferSize, inF)!=NULL) {
        size_t lengthOfString=strlen(tempString);
        while (lengthOfString>0 && tempString[lengthOfString-1]!='\n') {
            bufferSize*=2;
            tempString=realloc(tempString, bufferSize);
            if (fgets(tempString+lengthOfString, bufferSize-lengthOfString, inF) == NULL) //проверка на достижение конца файла
                break;
            lengthOfString+=strlen(tempString+lengthOfString);
        }
        char* word=strtok(tempString, " \n");
        while (word!=NULL) {
            if (strcmp(word, secondWord) == 0) {
                firstWord=checkWord (strlen(firstWord), firstWord);
                fprintf(outF, "%s", firstWord);
            }
            else {
                fprintf(outF, "%s", word);
            }
            word=strtok(NULL, " \n");
            if (word!=NULL)
                fprintf(outF, " ");
        }
        fprintf(outF, "\n");
    }
    fclose(inF);
    fclose(outF);
    remove("Text.txt");
    rename("ArchivedText.txt", "Text.txt");
    free(tempString);
}



int searchParagraph(FILE* inF, char* tempWord) {
    int positionOfParagraph=-1;
    while (fscanf(inF, "%s", tempWord) != EOF) {
        if (strcmp(tempWord, "*!*") == 0) {
            positionOfParagraph=ftell(inF);
            break;
        }
    }
    return positionOfParagraph;
}



int searchAmountOfWord(FILE* inF, char* buffer) {
    int amountOfWord=0;
    while (fscanf(inF, "%s", buffer)!=EOF)
        amountOfWord++;
    return amountOfWord;
}



char** memory(int amountOfWord) {
    char** word=malloc(amountOfWord*sizeof(char*));
    for (int i=0; i<amountOfWord; i++) {
        word[i]=malloc(100*sizeof(char));
    }
    return word;
}



void copyBufferToArray(FILE* text, char** words, char* buffer) {
    int index=0;
    while (fscanf(text, "%s", buffer)!=EOF) {
        strcpy(words[index], buffer);
        index++;
    }
}



void processingFile() {
    FILE *inpF=NULL;
    if ((inpF = fopen("Text.txt", "r"))== NULL) {
        printf("Error opening Text.txt!\n");
        exit(1);
    }
    FILE *outF=NULL;
    if ((outF = fopen("ArchivedText.txt", "w"))== NULL) {
        printf("Error opening ArchivedText.txt!\n");
        exit(1);
    }
    size_t bufferSize=1024;
    char* buffer=malloc(bufferSize);
    int countOfProcessingString=0;
    while (fgets(buffer, bufferSize, inpF)!=NULL) {
        size_t sizeOfString=strlen(buffer);
        while (sizeOfString>0 && buffer[sizeOfString-1]!='\n') {
            bufferSize*=2;
            buffer=realloc(buffer, bufferSize);
            if (fgets(buffer+sizeOfString, bufferSize-sizeOfString, inpF) == NULL)
                break;  //проверка на достижение конца файла
            sizeOfString+=strlen(buffer+sizeOfString);
        }
        char* word=strtok(buffer, " \n");
        while (word!=NULL) {
            if (strcmp(word, "*!*") == 0) {
                fseek(outF, -1, SEEK_CUR);
                break;
            }
            else {
                fprintf(outF, "%s", word);
                word=strtok(NULL, " \n");
                if (word!=NULL)
                    fprintf(outF, " ");
            }
        }
        if (word!=NULL)
            break;
        countOfProcessingString++;
        if (countOfProcessingString>=1)
            fprintf(outF, "\n");
    }
    free(buffer);
    fclose(inpF);
    fclose(outF);
    remove("Text.txt");
    rename("ArchivedText.txt", "Text.txt");
}

char** prepareToProcessing (char *tempWord, int *amountOfWord, char** words) {
    FILE *inF=NULL;
    if ((inF=fopen("Text.txt", "r"))== NULL) {
        printf("Error opening Text.txt!\n");
        exit(1);
    }
    int positionOfParagraph=searchParagraph(inF, tempWord);
    *amountOfWord=searchAmountOfWord(inF, tempWord);
    words=memory(*amountOfWord);
    fseek(inF, positionOfParagraph, SEEK_SET);
    copyBufferToArray(inF, words, tempWord);
    fclose(inF);
    for (int i=*amountOfWord-2; i>=0; i-=2) {
        replace(words[i], words[i+1]);
    }
    return words;
}
