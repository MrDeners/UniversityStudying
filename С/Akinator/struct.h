#define STRING_SIZE 1024


typedef struct treeStruct{
    char data[STRING_SIZE];
    struct treeStruct* left;
    struct treeStruct* right;
} tree;
