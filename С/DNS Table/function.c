#include "function.h"

#define MAX_DOMEN_SIZE 63
#define MAX_IP_SIZE 15
#define MAX_LINE_SIZE 88



void processing (int* operation, Cache **cache) {
    switch (*operation) {
        case 1:
            searchIPbyDomen(cache);
            break;
        case 2:
            searchAllDomen();
            break;
        case 3:
            addNewNote();
            break;
        case 4:
            outputAllCache (cache);
            break;

    }
}

void getDomen(char **domen) {
    printf("Input domen: ");
    scanf("%s", *domen);
}

void getKey(int *key, char *domen) {
    for (int i=0; i < strlen(domen); i++)
        *key += domen[i];
}

void cacheCreate(Cache **cache, int capacity) {
    (*cache)->capacity = capacity;
    (*cache)->size = 0;
    (*cache)->hashTable = calloc(capacity, sizeof(Node*));
    (*cache)->head = malloc(sizeof(Node));
    (*cache)->tail = malloc(sizeof(Node));
    (*cache)->head->prev = NULL;
    (*cache)->head->next = (*cache)->tail;
    (*cache)->tail->prev = (*cache)->head;
    (*cache)->tail->next = NULL;
}

int hash(int key, int capacity) {
    return key % capacity;
}

void moveToHead(Cache **cache, Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = (*cache)->head;
    node->next = (*cache)->head->next;
    (*cache)->head->next->prev = node;
    (*cache)->head->next = node;
}

void addToHead(Cache **cache, Node *node) {
    node->prev = (*cache)->head;
    node->next = (*cache)->head->next;
    (*cache)->head->next->prev = node;
    (*cache)->head->next = node;
    (*cache)->size++;
}

void removeTail(Cache **cache) {
    Node *node = (*cache)->tail->prev;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    int index = hash(node->key, (*cache)->capacity);
    (*cache)->hashTable[index] = NULL;
    free(node);
    (*cache)->size--;
}
void addFropmFile (Cache** cache, int key, int fl, char* domen) {
    FILE* file = fopen("DNS Table.txt", "r");
    if (!file) {
        printf("Error of opening DNS Table\n");
        return;
    }
    int startNewString;
    char startNewStringSym;
    char* PTRSrartNewStringSym;
    char* tempString = calloc(MAX_DOMEN_SIZE, sizeof(char));
    char* buffer = calloc(MAX_DOMEN_SIZE, sizeof(char));
    fl = 0;
    while (!feof(file)) {
        fgets(tempString, MAX_DOMEN_SIZE, file);
        if (strstr(tempString, domen) != NULL) {
            while (strstr(tempString, " A ") == NULL) {
                PTRSrartNewStringSym = strstr(tempString, " CNAME ");
                startNewStringSym = PTRSrartNewStringSym - tempString;
                startNewString = startNewStringSym - '0';
                strcpy(buffer, &tempString[startNewString+7]);
                fseek(file, 0, SEEK_SET);
                while (!feof(file)) {
                    fgets(tempString, MAX_DOMEN_SIZE, file);
                    if (strstr(tempString, buffer) != NULL)
                        break;
                }
            }
            PTRSrartNewStringSym = strstr(tempString, " A ");
            strcpy(buffer, &PTRSrartNewStringSym[3]);
            break;
        }
    }
    if (strcmp(buffer, "\0") == 0) {
        printf("This domain was not found.");
        return;
    }
    fclose(file);
    printf("%s", buffer);
    cachePut(cache, key, buffer, domen);
    free(tempString);
    free(buffer);
}

void cacheGet(Cache** cache, char* domen, int key) {
    int counter = 0;
    int fl = 0;
    Node *node = NULL;
    int index = hash(key, (*cache)->capacity);
    while ((*cache)->hashTable[index] != NULL && strcmp((*cache)->hashTable[index]->domen, domen) != 0) {
        index++;
        counter++;
        if (counter == (*cache)->capacity) {
            fl = 1;
            break;
        }
    }
    if (fl != 1)
        node = (*cache)->hashTable[index];
    if (node == NULL) {
        addFropmFile (cache, key, fl, domen);

    }
    else {
        moveToHead(cache, node);
        printf("%s", node->value);
    }
}

void cachePut(Cache** cache, int key, char* value, char* domen) {
    int index = hash(key, (*cache)->capacity);
    int counter = 0;
    int fl = 0;
    Node *node = NULL;
    
    while ((*cache)->hashTable[index] != NULL && strcmp((*cache)->hashTable[index]->domen, domen) != 0) {
        index++;
        counter++;
        if (counter == (*cache)->capacity) {
            fl = 1;
            break;
        }
    }
    if (fl != 1)
        node = (*cache)->hashTable[index];
    
    if (node == NULL) {
        node = (Node*)malloc(sizeof(Node));
        node->key = key;
        node->value = calloc(MAX_IP_SIZE, sizeof(char));
        node->domen = calloc(MAX_DOMEN_SIZE, sizeof(char));
        strcpy(node->value, value);
        strcpy(node->domen, domen);
        addToHead(cache, node);
        (*cache)->hashTable[index] = node;
        if ((*cache)->size > (*cache)->capacity) {
            removeTail(cache);
        }
    }
    else {
        node->value = value;
        moveToHead(cache, node);
    }
}

void cacheFree(Cache* cache) {
    Node *node = cache->head->next;
    while (node != cache->tail) {
        Node *next = node->next;
        free(node);
        node = next;
    }
    free(cache->head);
    free(cache->tail);
    free(cache->hashTable);
    free(cache);
}


void searchIPbyDomen (Cache **cache) {
    char *value = calloc(MAX_DOMEN_SIZE, sizeof(char));
    int key = 0;
    getDomen(&value);
    getKey(&key, value);
    cacheGet(cache, value, key);
    free(value);
}

void getNewDomen (char** newDomen) {
    int fl = 0;
    char* partOfDomen = calloc(MAX_DOMEN_SIZE, sizeof(char));
    
    printf("Input XXX:\tXXX.by\n");
    while(fgets(partOfDomen, MAX_DOMEN_SIZE-5, stdin)) {
        if (strlen(partOfDomen)>2 & partOfDomen[0] != '-' & partOfDomen[strlen(partOfDomen)-1] != '-') {
            for (int i=0; i<strlen(partOfDomen); i++) {
                if (partOfDomen[i] == '!' && partOfDomen[i] == '?' && partOfDomen[i] == '@' && partOfDomen[i] == '#' && partOfDomen[i] == '.' && partOfDomen[i] == '$' && partOfDomen[i] == '%' && partOfDomen[i] == '^' && partOfDomen[i] == '*' && partOfDomen[i] == '&' && partOfDomen[i] == '/')
                    fl = 1;
            }
            if (fl == 0)
            break;
            fl=0;
            printf("\nError: use letters, numbers and hyphen (Not the first or last character). No more that 57 characters.\n");
        }
    }
    partOfDomen[strlen(partOfDomen)-1] = '\0';
    strncat(*newDomen, partOfDomen, MAX_DOMEN_SIZE-6);
    
    strncat(*newDomen, ".", 1);
    
    printf("Input XXX:\tgoogle.XXX\n");
    while(fgets(partOfDomen, MAX_DOMEN_SIZE-57, stdin)) {
        if (strlen(partOfDomen)>2 & partOfDomen[0] != '-' & partOfDomen[strlen(partOfDomen)-1] != '-') {
            for (int i=0; i<strlen(partOfDomen); i++) {
                if (partOfDomen[i] == '!' && partOfDomen[i] == '?' && partOfDomen[i] == '@' && partOfDomen[i] == '#' && partOfDomen[i] == '.' && partOfDomen[i] == '$' && partOfDomen[i] == '%' && partOfDomen[i] == '^' && partOfDomen[i] == '*' && partOfDomen[i] == '&' && partOfDomen[i] == '/')
                    fl = 1;
            }
            if (fl == 0)
            break;
            fl=0;
            printf("\nError: use letters, numbers and hyphen (Not the first or last character). No more than 5 characters.\n");
        }
    }
    partOfDomen[strlen(partOfDomen)-1] = '\0';
    strncat(*newDomen, partOfDomen, MAX_DOMEN_SIZE-57);
    
    printf("\nYour inputting domen: %s \n", *newDomen);
    
    free(partOfDomen);
}

void inputNewSymbol (int num, char** newIP) {
    if (num == 0) strncat(*newIP, "0", 1);
    else if (num == 1) strncat(*newIP, "1", 1);
    else if (num == 2) strncat(*newIP, "2", 1);
    else if (num == 3) strncat(*newIP, "3", 1);
    else if (num == 4) strncat(*newIP, "4", 1);
    else if (num == 5) strncat(*newIP, "5", 1);
    else if (num == 6) strncat(*newIP, "6", 1);
    else if (num == 7) strncat(*newIP, "7", 1);
    else if (num == 8) strncat(*newIP, "8", 1);
    else if (num == 9) strncat(*newIP, "9", 1);
}

void addQuarterOfIp (int partOfIP, char** newIP) {
    int fl = 0;
    int tempSymbol = 0;
    tempSymbol = partOfIP / 100;
    if (tempSymbol != 0)
        inputNewSymbol (tempSymbol, newIP);
    else fl = 1;
    tempSymbol = ((partOfIP / 10) % 10);
    if (tempSymbol == 0 && fl == 1);
    else
        inputNewSymbol (tempSymbol, newIP);
    tempSymbol = partOfIP % 10;
    inputNewSymbol (tempSymbol, newIP);
}

void getNewIP (char** newIP) {
    int partOfIP = 0;
    printf("Input XXX:\tXXX.123.123.123\n");
    while(!scanf("%d", &partOfIP) || partOfIP<0 || partOfIP>255) {
        printf("ERROR: Input number (0<=XXX<=255)");
        rewind(stdin);
    }
    addQuarterOfIp(partOfIP, newIP);
    strncat(*newIP, ".", 1);
    
    printf("Input XXX:\t123.XXX.123.123\n");
    while(!scanf("%d", &partOfIP) || partOfIP<0 || partOfIP>255) {
        printf("ERROR: Input number (0<=XXX<=255)");
        rewind(stdin);
    }
    addQuarterOfIp(partOfIP, newIP);
    strncat(*newIP, ".", 1);
    
    printf("Input XXX:\t123.123.XXX.123\n");
    while(!scanf("%d", &partOfIP) || partOfIP<0 || partOfIP>255) {
        printf("ERROR: Input number (0<=XXX<=255)");
        rewind(stdin);
    }
    addQuarterOfIp(partOfIP, newIP);
    strncat(*newIP, ".", 1);
    
    printf("Input XXX:\t123.123.123.XXX\n");
    while(!scanf("%d", &partOfIP) || partOfIP<0 || partOfIP>255) {
        printf("ERROR: Input number (0<=XXX<=255)");
        rewind(stdin);
    }
    addQuarterOfIp(partOfIP, newIP);
    
    printf("\nYour inputting IP: %s \n", *newIP);
}

void availabilityCheck (char** domen, int* fl) {
    char* string = calloc(MAX_LINE_SIZE, sizeof(char));
    char* PTRfirstInputSym;
    int firstInput = 0;
    FILE* file = fopen("DNS Table.txt", "r");
    if (!file) {
        printf("Error of opening DNS Table\n");
        return;
    }
    while(!feof(file)) {
        fgets(string, MAX_LINE_SIZE, file);
        PTRfirstInputSym = strstr(string, *domen);
        if (PTRfirstInputSym != NULL) {
                if (memcmp(PTRfirstInputSym, string, 1) == 0)
                firstInput = 1;
        }
        if (firstInput == 1) {
            *fl = 1;
            break;
        }
    }
}

void choisOperation (int* operation) {
    printf("\n|------------------------------------------------------|\n");
    printf("Operations:\n");
    printf("1: Add domen of IP address\n");
    printf("2: Add domen of domen\n");
    printf("3: Close program\n");
    printf("\n");
    printf("Your choice: ");
    while(!scanf("%d", operation) || *operation<1 || *operation>3) {
        printf("Pleas, choice existing operation (1, 2 or 3).\n");
        printf("Your choice: ");
        rewind(stdin);
    }
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    if (*operation == 3) {
        printf("\n");
        return;
    }
}

void addNewNote () {
    int operation = 0;
    int fl = 0;
    char* newDomen = calloc(MAX_DOMEN_SIZE, sizeof(char));
    char* newIP = calloc(MAX_IP_SIZE, sizeof(char));
    char* newDomenOfDomen = calloc(MAX_DOMEN_SIZE, sizeof(char));
    char* newLine = calloc(MAX_LINE_SIZE, sizeof(char));
    FILE* file = fopen("DNS Table.txt", "a");
    if (!file) {
        printf("Error of opening DNS Table\n");
        return;
    }
    choisOperation (&operation);
    switch (operation){
        case 1:
            printf("Print new Domen:\n");
            getNewDomen (&newDomen);
            printf("\n");
            availabilityCheck (&newDomen, &fl);
            if (fl == 1) {
                printf("This domain is already in use.\n");
                return;
            }
            printf("Print new IP:\n");
            getNewIP (&newIP);
            strncat(newLine, newDomen, MAX_DOMEN_SIZE);
            strncat(newLine, " IN A ", 6);
            strncat(newLine, newIP, MAX_IP_SIZE);
            strncat(newLine, "\n", MAX_IP_SIZE);
            fputs(newLine, file);
            printf("Adding completed successfully!");
            break;
        case 2:
            printf("Print main Domen:\n");
            getNewDomen (&newDomen);
            availabilityCheck (&newDomen, &fl);
            if (fl == 0) {
                printf("This domen has not been entered before.\n");
                return;
            }
            printf("\n");
            printf("Print his Domen:\n");
            getNewDomen (&newDomenOfDomen);
            fl=0;
            availabilityCheck (&newDomenOfDomen, &fl);
            if (fl == 1) {
                printf("This domain is already in use.\n");
                return;
            }
            strncat(newLine, newDomenOfDomen, MAX_DOMEN_SIZE);
            strncat(newLine, " IN CNAME ", 10);
            strncat(newLine, newDomen, MAX_DOMEN_SIZE);
            strncat(newLine, "\n", MAX_IP_SIZE);
            fputs(newLine, file);
            printf("Adding completed successfully!");
            break;
    }
    fclose(file);
    free(newDomen);
    free(newIP);
    free(newDomenOfDomen);
    free(newLine);
}

void searchAllDomen () {
    char* tempDomen = calloc(MAX_DOMEN_SIZE, sizeof(char));
    char* IP = calloc(MAX_IP_SIZE, sizeof(char));
    char* buffer = calloc(MAX_IP_SIZE, sizeof(char));
    int counter = 0;
    int counterTwo = 0;
    int fl = 0;
    FILE* file = fopen("DNS Table.txt", "r");
    if (!file) {
        printf("Error of opening DNS Table\n");
        return;
    }
    getNewIP (&IP);
        while(!feof(file)) {
            fgets(tempDomen, MAX_DOMEN_SIZE, file);
            for (int i=0; i<strlen(tempDomen); i++){
                if (tempDomen[i] == ' ') {
                    ++counterTwo;
                    if (counterTwo == 3) {
                        counter++;
                        break;
                    }
                }
                ++counter;
            }
            strcpy(buffer, &tempDomen[counter]);
            buffer[strlen(buffer)-1] = '\0';
            counter = 0;
            counterTwo = 0;
            if (strstr(buffer, IP) != NULL) {
                for (int i=0; i<strlen(tempDomen); i++) {
                    if (tempDomen[i] == ' ') {
                        break;
                    }
                    counter++;
                }
                for (int i=0; strlen(tempDomen); i++) {
                    if (tempDomen[i] == ' ') {
                        tempDomen[i] = '\0';
                        break;
                    }
                }
                strcpy(IP, tempDomen);
                counter = 0;
                printf("%s\n", IP);
                fl=1;
                fseek(file, 0, SEEK_SET);
            }
        }
    if (fl == 0) printf("This IP has no domains.");
    free(tempDomen);
    free(IP);
    free(buffer);
}

void outputAllCache (Cache** cache) {
    Node *node = (*cache)->head->next;
    while (node != (*cache)->tail) {
        Node *next = node->next;
        printf("%s", node->value);
        node = next;
    }
}
