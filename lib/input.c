#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 128

// Function to get an integer
bool getNumber(const char *prompt, bool retryOnInvalid, long *result, size_t bufferSize) {
    char inputBuffer[bufferSize];

    while (true) {
        printf("%s: ", prompt);
        if (fgets(inputBuffer, bufferSize, stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");
            return false;
        }

        // Convert the string to an integer
        char *endptr;
        errno = 0;  // Reset errno before the call
        *result = strtol(inputBuffer, &endptr, 10);

        // Check conversion errors
        if ((errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN)) || (errno != 0 && *result == 0)) {
            perror("Conversion failed");
            return false;
        }

        // Check if conversion succeeded and the rest of the string is empty
        if (*endptr == '\0' || *endptr == '\n') {
            return true;
        } else {
            fprintf(stderr, "Invalid input. ");
            if (retryOnInvalid) {
                printf("Retry\n");
            } else {
                printf("\n");
            }

            if (!retryOnInvalid) {
                return false;
            }
        }
    }
}

// Function to get a decimal number
bool getDecimal(const char *prompt, bool retryOnInvalid, double *result, size_t bufferSize) {
    char inputBuffer[bufferSize];

    while (true) {
        printf("%s: ", prompt);
        if (fgets(inputBuffer, bufferSize, stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");
            return false;
        }

        // Save the user-input value before conversion
        double userInputValue;

        if (sscanf(inputBuffer, "%lf", &userInputValue) != 1) {
            fprintf(stderr, "Invalid input. ");
            if (retryOnInvalid) {
                printf("Retry\n");
            } else {
                printf("\n");
            }

            if (!retryOnInvalid) {
                return false;
            } else {
                continue;
            }
        }

        // Convert the string to a double
        char *endptr;
        errno = 0;  // Reset errno before the call
        *result = strtod(inputBuffer, &endptr);

        // Check conversion errors
        if ((errno == ERANGE && (*result == HUGE_VAL || *result == -HUGE_VAL)) || (errno != 0 && *result == 0)) {
            perror("Conversion failed");
            return false;
        }

        // Check if conversion succeeded and the rest of the string is empty
        if (*endptr == '\0' || *endptr == '\n') {
            return true;
        } else {
            fprintf(stderr, "Invalid input. ");
            if (retryOnInvalid) {
                printf("Retry\n");
            } else {
                printf("\n");
            }
            if (!retryOnInvalid) {
                return false;
            }
        }
    }
}

// Function to get a string
bool getInput(const char *prompt, bool retryOnInvalid, char *result, size_t bufferSize) {
    while (1) {
        printf("%s: ", prompt);

        if (fgets(result, bufferSize, stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");
            return false;
        }

        // Remove the newline character from the end of the string
        size_t length = strlen(result);
        if (length > 0 && result[length - 1] == '\n') {
            result[length - 1] = '\0';
        } else if (length == bufferSize - 1 && result[length - 1] != '\n') {
            // Clear the input buffer if the input is too long
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        // Check if a non-empty string is entered
        if (strlen(result) > 0) {
            return true;
        } else {
            fprintf(stderr, "Invalid input. Please try again.\n");

            if (!retryOnInvalid) {
                return false;
            }
        }
    }
}
