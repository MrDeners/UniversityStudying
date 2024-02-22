typedef struct Node {
    int key;
    char *value;
    char *domen;
    struct Node *prev;
    struct Node *next;
} Node;



typedef struct Cache {
    int capacity;
    int size;
    Node **hashTable;
    Node *head;
    Node *tail;
} Cache;
