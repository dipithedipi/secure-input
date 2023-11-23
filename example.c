#include "lib/input.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    long integerValue;
    double decimalValue;
    char stringValue[DEFAULT_BUFFER_SIZE];

    // Get an Integer (long int) and prompt until a valid number is entered
    getNumber("Enter an integer", true, &integerValue, DEFAULT_BUFFER_SIZE);
    printf("You entered the integer: %ld\n", integerValue);

    // Get an Integer (long int) and prompt only once, check if the number is valid (true)
    if (getNumber("Enter an integer", false, &integerValue, DEFAULT_BUFFER_SIZE)) {
        printf("You entered the integer: %ld\n", integerValue);
    } else {
        fprintf(stderr, "Error during integer input.\n");
        return 1;
    }

    // Get a Decimal (double) and prompt until a valid number is entered
    getDecimal("Enter a decimal number", false, &decimalValue, DEFAULT_BUFFER_SIZE);
    printf("You entered the decimal number: %lf\n", decimalValue);

    // Get a Decimal (double) and prompt only once, check if the decimal number is valid (true)
    if (getDecimal("Enter a decimal number", false, &decimalValue, DEFAULT_BUFFER_SIZE)) {
        printf("You entered the decimal number: %lf\n", decimalValue);
    } else {
        fprintf(stderr, "Error during decimal number input.\n");
        return 1;
    }

    // Get a String (char*) and prompt until a valid string is entered
    getInput("Enter a string", false, stringValue, DEFAULT_BUFFER_SIZE);
    printf("You entered the string: %s\n", stringValue);

    // Get a string and prompt only once, check if the string is valid (true)
    if (getInput("Enter a string", false, stringValue, DEFAULT_BUFFER_SIZE)) {
        printf("You entered the string: %s\n", stringValue);
    } else {
        fprintf(stderr, "Error during string input.\n");
        return 1;
    }

    return 0;
}
