#include <stdio.h>
#include <stdlib.h>

int main() {
    char *num=NULL;
    int numOfArray=0;
    num=calloc(1, sizeof(char));
    int memoryName = 1;
    int index=1;
       while((num[index-1]=getchar())!='\n') {
           if (index>=memoryName) {
               memoryName++;
               num = realloc(num, memoryName * sizeof(char));
           }
           index++;
       }
        memoryName++;
        num = realloc(num, memoryName * sizeof(char));
    num[index-1]='\0';
    numOfArray=memoryName-2;

    for (int i=1; i<numOfArray; i++) {
        int number=i;
        while (number-1>=0 && num[number]>num[number-1]) {
            int temp = num[number-1];
            num[number-1]=num[number];
            num[number]=temp;
            number--;
        }
    }
    printf("%s", num);
    return 0;
}
