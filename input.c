#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 128

bool getNumber(const char *prompt, bool retryOnInvalid, long *result, size_t bufferSize) {
    char inputBuffer[bufferSize];

    while (true) {
        printf("%s: ", prompt);
        if (fgets(inputBuffer, bufferSize, stdin) == NULL) {
            fprintf(stderr, "Errore durante la lettura dell'input.\n");
            return false;
        }

        // Converti la stringa in un numero intero
        char *endptr;
        errno = 0;  // Resetta errno prima della chiamata
        *result = strtol(inputBuffer, &endptr, 10);

        // Controlla gli errori di conversione
        if ((errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN)) || (errno != 0 && *result == 0)) {
            perror("Conversione fallita");
            return false;
        }

        // Controlla se la conversione è riuscita e se il resto della stringa è vuoto
        if (*endptr == '\0' || *endptr == '\n') {
            return true;
        } else {
            fprintf(stderr, "Input non valido. Riprova.\n");

            if (!retryOnInvalid) {
                return false;
            }
        }
    }
}

bool getDecimal(const char *prompt, bool retryOnInvalid, double *result, size_t bufferSize) {
    char inputBuffer[bufferSize];

    while (true) {
        printf("%s: ", prompt);
        if (fgets(inputBuffer, bufferSize, stdin) == NULL) {
            fprintf(stderr, "Errore durante la lettura dell'input.\n");
            return false;
        }

        // Salva il valore inserito dall'utente prima della conversione
        double userInputValue;

        if (sscanf(inputBuffer, "%lf", &userInputValue) != 1) {
            fprintf(stderr, "Input non valido. Riprova.\n");

            if (!retryOnInvalid) {
                return false;
            } else {
                continue;
            }
        }

        // Converti la stringa in un numero double
        char *endptr;
        errno = 0;  // Resetta errno prima della chiamata
        *result = strtod(inputBuffer, &endptr);

        // Controlla gli errori di conversione
        if ((errno == ERANGE && (*result == HUGE_VAL || *result == -HUGE_VAL)) || (errno != 0 && *result == 0)) {
            perror("Conversione fallita");
            return false;
        }

        // Controlla se la conversione è riuscita e se il resto della stringa è vuoto
        if (*endptr == '\0' || *endptr == '\n') {
            return true;
        } else {
            fprintf(stderr, "Input non valido. Riprova.\n");

            if (!retryOnInvalid) {
                return false;
            }
        }
    }
}

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

int main(void) {
    char inputString[DEFAULT_BUFFER_SIZE];

    // Esempio di utilizzo della funzione getInput
    if (getInput("Inserisci una stringa", true, inputString, sizeof(inputString))) {
        printf("Hai inserito: %s\n", inputString);
    } else {
        printf("Input non valido.\n");
    }

    printf("%lu\n",sizeof(inputString));


    return 0;
}
