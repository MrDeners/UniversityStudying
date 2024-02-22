#include "function.h"


int main() {
    tree* headOfBinaryTree = malloc(sizeof(tree));
    game(headOfBinaryTree);
    treeCleaning(headOfBinaryTree);
    printf("Good Bye!\n");
    return 0;
}
