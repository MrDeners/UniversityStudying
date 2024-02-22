#define ANSWER_SIZE 5
#include "function.h"


void game(tree* headOfBinaryTree) {
    tree* binaryTree = headOfBinaryTree;
    int line = 1;
    int maxLine = 1;
    bool answer = false;
    char* answerChar = calloc(ANSWER_SIZE, sizeof(char));
    printf("Guess your Blogger.\n\n\n");
    askAndAnswer(&binaryTree, line, maxLine);
    printf("Do you want to start a next try?\n");
    getAnswer(&answer, answerChar);
    free (answerChar);
    binaryTree = headOfBinaryTree;
    if (answer == true)
        game(headOfBinaryTree);
    else return;
}

