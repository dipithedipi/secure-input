#include <stdbool.h>
#include <stdio.h>
#include "../lib/input.h"

int main() {
    long number;
    bool res;

    res = getNumber("Inserisci un numero intero", false, &number, 20);
    printf("numero: %ld", number);

    return 0;
}
