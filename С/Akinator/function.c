#define STRING_SIZE 1024
#define ANSWER_SIZE 5
#include "function.h"


void askAndAnswer(tree** binaryTree, int line, int maxLine) {
    char* tempData = calloc(STRING_SIZE, sizeof(char));
    char* answerChar = calloc(ANSWER_SIZE, sizeof(char));
    char* searchQuery = calloc(ANSWER_SIZE, sizeof(char));
    char* command = calloc(STRING_SIZE, sizeof(char));
    bool answer = true;
    bool endOfGame = false;
    int fl = 0;
    if ((*binaryTree)->data[0] == '\0') {
        fl = 1;
        searchString(&tempData, line);
    }
    if (strcmp(tempData, "\n") == 0)
        addNode(binaryTree, &tempData, line, &maxLine, &endOfGame);
    else {
        if (fl == 1)
            strcpy((*binaryTree)->data, tempData);
        if (strstr ((*binaryTree)->data, "?|?") != NULL) {
            for (int i=0; i<strlen((*binaryTree)->data); i++) {
                if ((*binaryTree)->data[i-1] == '?' && (*binaryTree)->data[i] == '|' && (*binaryTree)->data[i+1] == '?') {
                    printf("\n");
                    break;
                }
                printf("%c", (*binaryTree)->data[i]);
            }
        }
        else printf("%s", (*binaryTree)->data);
        getAnswer(&answer, answerChar);
        if (answer == true) {
            if (strstr ((*binaryTree)->data, "?|?")) {
                searchOnTheInternet (*binaryTree, searchQuery, command);
                return;
            }
            line = line * 2 + 1;
            binaryTree = &(*binaryTree)->right;
            if (*binaryTree == NULL)
            *binaryTree = newBranch(*binaryTree);
        }
        if (answer == false) {
            line = line * 2;
            binaryTree = &(*binaryTree)->left;
            if (*binaryTree == NULL)
            *binaryTree = newBranch(*binaryTree);
        }
    }
    free(tempData);
    free(answerChar);
    free(searchQuery);
    free(command);
    if (endOfGame == true)
        return;
    else askAndAnswer(binaryTree, line, maxLine);
}

void searchOnTheInternet (tree* binaryTree, char* searchQuery, char* command) {
    if (strstr ((*binaryTree).data, "?|?")) {
        strcpy(searchQuery, (*binaryTree).data);
        for (int i=0; i<strlen(searchQuery); i++) {
            searchQuery[i] = searchQuery[i+6];
            if (i == (strlen(searchQuery) - 1))
                searchQuery[i+1] = '?';
        }
        for (int j=0; j<strlen(searchQuery); j++) {
            if (searchQuery[j] == '?') {
                searchQuery[j] = '\0';
                break;
            }
        }
        for (int i=0; i<strlen(searchQuery); i++) {
            if (searchQuery[i] == ' ')
                searchQuery[i] = '-';
        }
        sprintf(command, "open https://www.bing.com/search?q=%s", searchQuery);
        system(command);
    }
}

tree* newBranch(tree* binaryTree) {
    binaryTree = malloc(sizeof(tree));
    binaryTree->left = NULL;
    binaryTree->right = NULL;
    return binaryTree;
}

void searchString(char** tempData, int line) {
    int counter = 0;
    FILE* file = fopen("DataBase.txt", "r");
    if (!file) {
        printf("Error of opening DataBase");
        return;
    }
    while(!feof(file)) {
        fgets(*tempData, STRING_SIZE, file);
        counter++;
        if (counter == line)
            break;
    }
    fclose(file);
}

void getAnswer(bool* answer, char* answerChar) {
    fgets(answerChar, STRING_SIZE, stdin);
    for (int i = 0; i < strlen(answerChar); i++)
        if (answerChar[i] == '\n')
            answerChar[i] = '\0';
    if (strcmp(answerChar, "yes") == 0 || strcmp(answerChar, "Yes") == 0 || strcmp(answerChar, "YES") == 0)
        *answer = true;
    else if (strcmp(answerChar, "no") == 0 || strcmp(answerChar, "No") == 0 || strcmp(answerChar, "NO") == 0 || strcmp(answerChar, "nO") == 0)
        *answer = false;
    else {
        printf("Error! Type yes/no!\n");
        getAnswer(&(*answer), answerChar);
    }
}

tree* newNode(char* string) {
    tree* buffer = malloc(sizeof(tree));
    strcpy(buffer->data, string);
    buffer->left = NULL;
    buffer->right = NULL;
    return buffer;
}

void addNode(tree** binaryTree, char** tempData, int line, int* maxLine, bool* endOfGame) {
    char* tempResult = calloc(STRING_SIZE, sizeof(char));
    char* newResult = calloc(STRING_SIZE, sizeof(char));
    char* tempQuestion = calloc(STRING_SIZE, sizeof(char));
    char* copiedString = calloc(STRING_SIZE, sizeof(char));
    bool complitedCycle = false;
    int counter = 0;
    FILE* file = fopen("DataBase.txt", "r");
    if (!file) {
        printf("Error of opening DataBase");
        return;
    }
    FILE* newFile = fopen("NewDataBase.txt", "w");
    if (!file) {
        printf("Error of creating NewDataBase");
        return;
    }
    printf("Who is it?\n");
    fgets(tempResult, STRING_SIZE, stdin);
    for (int i = 0; i < strlen(tempResult); i++)
        if (tempResult[i] == '\n')
            tempResult[i] = '\0';
    strcat(newResult, "It is ");
    strcat(newResult, tempResult);
    strcat(newResult, "?|?");
    printf("What a question can be asked to %s?\n", tempResult);
    fgets(tempQuestion, STRING_SIZE, stdin);
    strcpy((*binaryTree)->data, tempQuestion);
    (*binaryTree)->right = newNode(newResult);
    while (!feof(file)) {
        counter++;
        if (counter == line) {
            fgets(copiedString, STRING_SIZE, file);
            fputs(tempQuestion, newFile);
            while (!feof(file)) {
                counter++;
                if (counter == ((line * 2) + 1)) {
                    fgets(copiedString, STRING_SIZE, file);
                    fputs(newResult, newFile);
                }
                else {
                    fgets(copiedString, STRING_SIZE, file);
                    fputs(copiedString, newFile);
                }
                complitedCycle = true;
            }
        }
        else {
            fgets(copiedString, STRING_SIZE, file);
            fputs(copiedString, newFile);
        }
        if (complitedCycle == true)
            break;
    }
    if (*maxLine < ((line * 5) + 3))
        *maxLine = ((line * 5) + 3);
    while (counter <= (*maxLine + 1)) {
        counter++;
        fputs("\n", newFile);
    }
    *endOfGame = true;
        remove("DataBase.txt");
        rename("NewDataBase.txt", "DataBase.txt");
        fclose(file);
        fclose(newFile);
        free(tempResult);
        free(tempQuestion);
        free(copiedString);
}

void treeCleaning(tree* root) {
    if (root == NULL) return;
    treeCleaning(root->left);
    treeCleaning(root->right);
    free(root);
}
