#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n=0, k=0, a=0, b=0, op=0;
    char *x, *y, *z, *tempX, *tempY;
    char *temp=calloc(10, sizeof(char));
    int numOfX=1, numOfY=1;
    int fl=0;
    long xInt=0, yInt=0, zInt=0;
    x=calloc(2, sizeof(char));
    x[0]='0';
    y=calloc(2, sizeof(char));
    y[0]='0';
    z=calloc(10, sizeof(char));
    tempX=calloc(2, sizeof(char));
    tempY=calloc(2, sizeof(char));
    scanf ("%d", &n);
    
    while (op!=n) {
        op++;
        
        int index=1;
        if (fl==0) {
            getchar();
        }
        while((temp[index-1]=getchar())!='\n'){
            index++;
        };
        k=temp[2]-'0';
        a=temp[4]-'0';
        b=temp[6]-'0';
        switch (temp[0]-'0') {
            case 1:
                numOfX++;
                x=realloc(x, numOfX*sizeof(char));
                for(int i=numOfX-1; i>k; i--)
                    x[i]=x[i-1];
                numOfY++;
                sprintf(tempX, "%d", a);
                x[k]=tempX[0];
                y=realloc(y, numOfY*sizeof(char));
                for(int i=numOfY-1; i>k; i--)
                    y[i]=y[i-1];
                sprintf(tempY, "%d", b);
                y[k]=tempY[0];
                break;
            case 2:
                for (int i=k; i<numOfX; i++) {
                    x[i]=x[i+1];
                }
                numOfX--;
                x=realloc(x, numOfX*sizeof(char));
                for (int i=k; i<numOfY; i++) {
                    y[i]=y[i+1];
                }
                numOfY--;
                y=realloc(y, numOfY*sizeof(char));
                break;
            case 3:
                xInt=strtol(x, NULL, 10);
                yInt=strtol(y, NULL, 10);
                zInt=xInt+yInt;
                sprintf(z, "%ld", zInt);
                unsigned int numOfZ=strlen(z);
                if (numOfZ<k) {
                    printf("-1\n");
                    break;
                }
                else {
                    putchar(z[k-1]);
                }
                break;
        }
        fl=1;
    }
    return 0;
}
