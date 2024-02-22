#include "function.h"



void programWork (Cache **cache) {
    int operation=0;
       printf("\n|------------------------------------------------------|\n");
       printf("Operations:\n");
       printf("1: Find IP address by Domen\n");
       printf("2: Find all DNS by IP address\n");
       printf("3: Add new IP address\n");
       printf("4: Output all cache\n");
       printf("5: Close program\n");
       printf("\n");
       printf("Your choice: ");
       while(!scanf("%d", &operation) || operation<1 || operation>5) {
           printf("Pleas, choice existing operation (1, 2, 3, 4 or 5).\n");
           printf("Your choice: ");
           rewind(stdin);
       }
       printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
       if (operation == 5) {
           printf("\n");
           return;
       }
    processing (&operation, &(*cache));
    programWork(cache);
}



