#include <stdio.h>
#include <stdlib.h>

int main() {
    int numOfCase=0;
    int rez=0;
    int pos=0;
    scanf("%d", &numOfCase);
    numOfCase++;
    int num[numOfCase];
    for (int i=0; i<numOfCase; i++) {
        scanf("%d", &num[i]);
    }
    for (int j=0; j<9; j++) {
        for (int i=0; i<numOfCase; i++) {
            if(num[i]==0) {
                pos=i;
                break;
            }
        }
        for (int i=0; i<numOfCase; i++) {
            if (num[i]==pos) {
                int temp=num[i];
                num[i]=num[pos];
                num[pos]=temp;
                rez++;
                break;
            }
        }
    }
    return 0;
}
