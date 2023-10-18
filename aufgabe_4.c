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
    int a = 42;
    int b = 41;
    int c = differenz(a, b);

    printf("%d - %d = %d\n", a, b, c);

    // Teilaufgabe b) ab hier:
    printf("Die Differenz von %d und %d ist %d. Der Abstand ist %d.\n", 5, 8, differenz(5, 8), absolut(differenz(5, 8)));
    printf("Die Differenz von %d und %d ist %d. Der Abstand ist %d.\n", 9, 2, differenz(9, 2), absolut(differenz(9, 2)));

    return 0;
}