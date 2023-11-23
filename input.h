#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 128

bool getNumber(const char *prompt, bool retryOnInvalid, long *result, size_t bufferSize);

bool getDecimal(const char *prompt, bool retryOnInvalid, double *result, size_t bufferSize);

bool getInput(const char *prompt, bool retryOnInvalid, char *result, size_t bufferSize);

#endif /* INPUT_H */