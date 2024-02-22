#include <stdio.h>

int main() {
    int ticket=0;
    scanf("%d", &ticket);
    while (!(ticket%100==42)) {
        ticket++;
    }
    printf("%d", ticket);
    
    return 0;
}
