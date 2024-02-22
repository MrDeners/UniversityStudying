#include "Struct.h"
#include "function.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int choiceOperation(phones *catalog, int operation, int numOfStruct) {
    switch(operation) {
        case 1: outputStruct(catalog, numOfStruct);
            break;
        case 2: numOfStruct=structDelet(catalog, numOfStruct);
            break;
        case 3: catalog=choiceSort(catalog, numOfStruct);
            break;
        case 4: catalog=startPosition (catalog, numOfStruct);
            break;
    }
    return numOfStruct;
}



phones* structArrayMemory (phones *catalog, int numOfStruct) {
    catalog=calloc(numOfStruct, sizeof(phones));
    return catalog;
}

char* inputString(char* tempName) {
    int memoryName = 1;
    int index=1;
       getchar();
       while((tempName[index-1]=getchar())!='\n') {
           if (index>=memoryName) {
               memoryName++;
               tempName = realloc(tempName, memoryName * sizeof(char));
           }
           index++;
       }
        memoryName++;
        tempName = realloc(tempName, memoryName * sizeof(char));
    tempName[index-1]='\0';
    return tempName;
}

phones* inputStruct (phones *catalog, int i) {
    char *tempName = calloc(1, 1 * sizeof(char));
    
    unsigned tempRAM;
    double tempDiagonal;
    printf("Name: ");
    tempName = inputString(tempName);
    printf("Diagonal: ");
    while(!scanf("%lf", &tempDiagonal) && tempDiagonal>0) {
        printf("Pleas, input number (>0)\n");
        rewind(stdin);
    }
    printf("RAM: ");
    while(!scanf("%d", &tempRAM) && tempDiagonal>0) {
        printf("Pleas, input number (>0)\n");
        rewind(stdin);
    }
    printf("\t0 - Black\n");
    printf("\t1 - White\n");
    printf("\t2 - Silver\n");
    printf("\t3 - Blue\n");
    printf("\t4 - Yellow\n");
    printf("\t5 - Green\n");
    printf("\t6 - Brown\n");
    printf("\t7 - Red\n");
    printf("\t8 - Purple\n");
    printf("\t9 - Orange\n");
    printf("\t10 - Pink\n");
    printf("\t11 - Grey\n");
    printf("\t12 - Violet\n");
    printf("Color: ");
    while(!scanf("%d", &catalog[i].COLOR) && tempDiagonal>=0 && tempDiagonal<=12) {
        printf("Pleas, input number (>0)\n");
        rewind(stdin);
    }
    printf("\n");
    catalog[i].ID=(i+1);
    catalog[i].name=calloc(1, 1 * sizeof(char));
    strcpy(catalog[i].name, tempName);
    catalog[i].diagonal=tempDiagonal;
    catalog[i].RAM=tempRAM;
    return catalog;
}

phones* structCreate(phones *catalog, int numOfStruct) {
    catalog=structArrayMemory(catalog, numOfStruct);
    printf("\n");
    for (int i=0; i<numOfStruct; i++) {
        inputStruct(catalog, i);
    }
    return catalog;
}

void outputStruct(phones *catalog, int numOfStruct) {
    for (int i=0; i<numOfStruct; i++) {
        printf("\n\n");
        printf("Name:\t\t"); puts(catalog[i].name); printf("ID:\t\t\t[%d]", catalog[i].ID); printf("\n");
        printf("Diagonal:\t"); printf("%.1lf", catalog[i].diagonal); printf("\n");
        printf("RAM:"); printf("%10d", catalog[i].RAM); printf("\n");
        printf("Color:\t\t");
        switch(catalog[i].COLOR) {
            case 0: printf("Black\n"); break;
            case 1: printf("White\n"); break;
            case 2: printf("Silver\n"); break;
            case 3: printf("Blue\n"); break;
            case 4: printf("Yellow\n"); break;
            case 5: printf("Green\n"); break;
            case 6: printf("Brown\n"); break;
            case 7: printf("Red\n"); break;
            case 8: printf("Purple\n"); break;
            case 9: printf("Orange\n"); break;
            case 10: printf("Pink\n"); break;
            case 11: printf("Grey\n"); break;
            case 12: printf("Violet\n"); break;
        }
    }
    printf("\n\n");
}

int firstSortingMenu (int sortParameter) {
    printf("|------------------------------------------------------|\n");
    printf("First parameter of sorting:\n");
    printf("1: Name\n");
    printf("2: Diagonal\n");
    printf("3: RAM\n");
    printf("4: Color\n");
    printf("5: Return to main menu\n");
    printf("\n");
    printf("Your choice: ");
    while(!scanf("%d", &sortParameter) || sortParameter<1 || sortParameter>5) {
        printf("Pleas, choice existing operation (1, 2, 3, 4 or 5).\n");
        printf("Your choice: ");
        rewind(stdin);
    }
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    return sortParameter;
}

int secondSortingMenu (int sortParameter) {
    printf("|------------------------------------------------------|\n");
    printf("Second parameter of sorting:\n");
    printf("1: Name\n");
    printf("2: Diagonal\n");
    printf("3: RAM\n");
    printf("4: Color\n");
    printf("5: Return to main menu\n");
    printf("\n");
    printf("Your choice: ");
    while(!scanf("%d", &sortParameter) || sortParameter<1 || sortParameter>5) {
        printf("Pleas, choice existing operation (1, 2, 3, 4 or 5).\n");
        printf("Your choice: ");
        rewind(stdin);
    }
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    return sortParameter;
}

int cmpCOLOR(void *a, void *b) {
    phones* s1=(phones*) a;
    phones* s2=(phones*) b;
    int result = s1->COLOR-s2->COLOR;
    if (s1->COLOR-s2->COLOR<0 && s1->COLOR-s2->COLOR>-1) {
        result = -1;
    }
    return result;
}

int cmpDiagonal(void *a, void *b) {
    phones* s1=(phones*) a;
    phones* s2=(phones*) b;
    int result = s1->diagonal-s2->diagonal;
    if (s1->diagonal-s2->diagonal<0 && s1->diagonal-s2->diagonal>-1) {
        result = -1;
    }
    return result;
}

int cmpRAM(void *a, void *b) {
    phones* s1=(phones*) a;
    phones* s2=(phones*) b;
    int result = s1->RAM-s2->RAM;
    if (s1->RAM-s2->RAM<0 && s1->RAM-s2->RAM>-1) {
        result = -1;
    }
    return result;
}

long cmpName(void *a, void *b) {
    phones* s1=(phones*) a;
    phones* s2=(phones*) b;
    return s1->name-s2->name;
}

phones* sort(phones *catalog, int numOfStruct, int (*cmpOne)(void*, void*), int (*cmpTwo)(void*, void*)) {
    for (int i=1; i<numOfStruct; i++) {
        int number=i;
        while (number-1>=0 && cmpOne(&catalog[number], &catalog[number-1])<0) {
            phones temp = catalog[number];
            catalog[number] = catalog[number-1];
            catalog[number-1] = temp;
            number--;
        }
        while (number-1>=0 && cmpOne(&catalog[number], &catalog[number-1])==0 && cmpTwo(&catalog[number], &catalog[number-1])<0) {
            phones temp = catalog[number];
            catalog[number] = catalog[number-1];
            catalog[number-1] = temp;
            number--;
        }
    }
    return catalog;
}

phones* choiceSort(phones* catalog, int numOfStruct) {
    int firstSortParameter=0, secondSortParameter=0;
    firstSortParameter=firstSortingMenu(firstSortParameter);
    secondSortParameter=secondSortingMenu(secondSortParameter);
    switch (firstSortParameter) {
        case 1:  //name
            switch (secondSortParameter) {
                case 1: catalog=sort(catalog, numOfStruct, &cmpName, &cmpName);
                    break;
                case 2: catalog=sort(catalog, numOfStruct, &cmpName, &cmpDiagonal);
                    break;
                case 3: catalog=sort(catalog, numOfStruct, &cmpName, &cmpRAM);
                    break;
                case 4: catalog=sort(catalog, numOfStruct, &cmpName, &cmpCOLOR);
                    break;
                case 5: return catalog;
                    break;
            }
            break;
        case 2:  //diagonal
            switch (secondSortParameter) {
                case 1: catalog=sort(catalog, numOfStruct, &cmpDiagonal, &cmpName);
                    break;
                case 2: catalog=sort(catalog, numOfStruct, &cmpDiagonal, &cmpDiagonal);
                    break;
                case 3: catalog=sort(catalog, numOfStruct, &cmpDiagonal, &cmpRAM);
                    break;
                case 4: catalog=sort(catalog, numOfStruct, &cmpDiagonal, &cmpCOLOR);
                    break;
                case 5: return catalog;
                    break;
            }
            break;
        case 3: //ram
            switch (secondSortParameter) {
                case 1: catalog=sort(catalog, numOfStruct, &cmpRAM, &cmpName);
                    break;
                case 2: catalog=sort(catalog, numOfStruct, &cmpRAM, &cmpDiagonal);
                    break;
                case 3: catalog=sort(catalog, numOfStruct, &cmpRAM, &cmpRAM);
                    break;
                case 4: catalog=sort(catalog, numOfStruct, &cmpRAM, &cmpCOLOR);
                    break;
                case 5: return catalog;
                    break;
            }
            break;
        case 4: //color
            switch (secondSortParameter) {
                case 1: catalog=sort(catalog, numOfStruct, &cmpCOLOR, &cmpName);
                    break;
                case 2: catalog=sort(catalog, numOfStruct, &cmpCOLOR, &cmpDiagonal);
                    break;
                case 3: catalog=sort(catalog, numOfStruct, &cmpCOLOR, &cmpRAM);
                    break;
                case 4: catalog=sort(catalog, numOfStruct, &cmpCOLOR, &cmpCOLOR);
                    break;
                case 5: return catalog;
                    break;
            }
            break;
        case 5: return catalog;  //exit
            break;
    }
    outputStruct(catalog, numOfStruct);
    return catalog;
}

phones* startPosition (phones *catalog, int numOfStruct) {
    for (int i=1; i<numOfStruct; i++) {
        int number=i;
        while (number-1>=0 && catalog[number].ID<catalog[number-1].ID) {
            phones temp = catalog[number];
            catalog[number] = catalog[number-1];
            catalog[number-1] = temp;
            number--;
        }
    }
    outputStruct(catalog, numOfStruct);
    return catalog;
}

int structDelet (phones *catalog, int numOfStruct) {
    catalog=startPosition (catalog, numOfStruct);
    int numOfDelet=0;
    printf("Input phone's ID (It's will by deleted): ");
    while(!scanf("%d", &numOfDelet) && numOfDelet>0) {
        printf("Pleas, input phone's ID (>0)\n");
        rewind(stdin);
    }
    if (numOfDelet>numOfStruct) {
        printf("The struct don't have %d elements\n", numOfDelet);
        return numOfStruct;
    }
    for (int i=0; i<numOfStruct; i++) {
        if (catalog[i].ID==numOfDelet && numOfStruct==numOfDelet) {
            numOfStruct--;
            catalog=realloc(catalog, (numOfStruct)*sizeof(phones));
        }
        else if (catalog[i].ID==numOfDelet) {
            catalog[i]=catalog[numOfStruct-1];
            numOfStruct--;
            catalog=realloc(catalog, (numOfStruct)*sizeof(phones));
        }
    }
    outputStruct(catalog, numOfStruct);
    return numOfStruct;
}

void structCleaning (phones *catalog, int numOfStruct) {
    for(int i=0; i<numOfStruct; i++) {
        free(catalog[i].name);
    }
    free(catalog);
}

