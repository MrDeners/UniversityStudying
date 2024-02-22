#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "menu.h"


void askAndAnswer(tree** binaryTree, int line, int maxLine);
void searchString(char** tempData, int line);
void treeCreate(tree** binaryTree);
void getAnswer(bool* answer, char* answerChar);
void addNode(tree** binaryTree, char** tempData, int line, int* maxLine, bool* endOfGame);
tree* newNode(char* string);
tree* newBranch(tree* binaryTree);
void treeCleaning(tree* root);
void searchOnTheInternet (tree* binaryTree, char* searchQuery, char* command);
