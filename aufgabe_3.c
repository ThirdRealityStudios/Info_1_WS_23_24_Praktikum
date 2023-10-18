#include <stdio.h>
int differenz(int a, int b){
    return a - b;
}

int main(){
    int a = 42;
    int b = 41;
    int c = differenz(a, b);

    printf("%d - %d = %d\n", a, b, c);
    return 0;
}