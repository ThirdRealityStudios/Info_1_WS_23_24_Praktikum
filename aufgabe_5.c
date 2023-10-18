#include <stdio.h>
int differenz(int a, int b){
    return a - b;
}

// Teilaufgabe a): Geforderte Zusatzfunktion für den Absolutbetrag.
int absolut(int zahl)
{
    return (zahl < 0) ? -zahl : zahl;
}

int main(){

    printf("| a     | b     | Differenz     | Abstand\n");    

    for(int i = 0; i <= 41; i++)
        printf("-");

    puts("");

    for(int i = 0; i <= 20; i = i + 1){
        int a = i; int b = 20 - i;
        printf("|%d\t|%d\t|a - b = %3d\t|%2d\n", a, b, differenz(a, b), absolut(differenz(a, b)));
    }



    return 0;
}