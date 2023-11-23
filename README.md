# Secure Input Library

This library provides functions for take the user input(stdin) in C language, with support for integers, decimals, and strings, the input will be controlled in such a way that overflows do not occur and characters that are not suitable for that input will not be inserted

## Functions

### `bool getNumber(const char *prompt, bool retryOnInvalid, long *result, size_t bufferSize)`

This function prompts the user for input with the specified prompt and attempts to read a long integer from the standard input. It handles input validation, retrying on invalid input if specified.

- Parameters:
  - `prompt`: The prompt to display to the user.
  - `retryOnInvalid`: If true, the function will prompt the user to retry on invalid input.
  - `result`: A pointer to store the result of the input (long integer).
  - `bufferSize`: The size of the input buffer.

### How It Works:

1. The function uses a loop to continually prompt the user for input until a valid integer is entered or the program encounters an error.

2. The prompt is displayed to the user using `printf`.

3. The input is read from the user using `fgets` and stored in the `inputBuffer`.

4. The function attempts to convert the string in `inputBuffer` to a long integer using `strtol`. The result is stored in the variable pointed to by `result`.

5. Conversion errors are checked:
   - If `errno` is set to `ERANGE` and the result is `LONG_MAX` or `LONG_MIN`, or if `errno` is nonzero and the result is zero, an error message is printed using `perror`, and the function returns `false`.

6. The function checks if the conversion succeeded and if the rest of the string is empty (i.e., the entire input was consumed):
   - If true, the function returns `true` indicating a successful input.
   - If false, an error message is printed, and the behavior depends on the value of `retryOnInvalid`:
     - If `retryOnInvalid` is `true`, the user is prompted to retry, and the loop continues.
     - If `retryOnInvalid` is `false`, the function returns `false`.

### Example Usage:

```c
long integerValue;

// Example 1: Prompt and retry until a valid integer is entered
getNumber("Enter an integer", true, &integerValue, DEFAULT_BUFFER_SIZE);

// Example 2: Prompt only once, check if the entered integer is valid
if (getNumber("Enter an integer", false, &integerValue, DEFAULT_BUFFER_SIZE)) {
    printf("You entered the integer: %ld\n", integerValue);
} else {
    fprintf(stderr, "Error during integer input.\n");
}
```

### `bool getDecimal(const char *prompt, bool retryOnInvalid, double *result, size_t bufferSize)`

Similar to `getNumber`, this function prompts the user for input with the specified prompt and attempts to read a double from the standard input. It handles input validation for decimals, retrying on invalid input if specified.

- Parameters:
  - `prompt`: The prompt to display to the user.
  - `retryOnInvalid`: If true, the function will prompt the user to retry on invalid input.
  - `result`: A pointer to store the result of the input (double).
  - `bufferSize`: The size of the input buffer.

### How It Works:

1. The function uses a loop to continually prompt the user for input until a valid decimal number is entered or the program encounters an error.

2. The prompt is displayed to the user using `printf`.

3. The input is read from the user using `fgets` and stored in the `inputBuffer`.

4. The function attempts to read a decimal number from the string in `inputBuffer` using `sscanf`. The result is stored in the variable `userInputValue`.

5. If `sscanf` fails to read a valid decimal number (returns a value other than 1), an error message is printed, and the behavior depends on the value of `retryOnInvalid`:
   - If `retryOnInvalid` is `true`, the user is prompted to retry, and the loop continues.
   - If `retryOnInvalid` is `false`, the function returns `false`.

6. If `sscanf` successfully reads a decimal number, the function attempts to convert the string to a double using `strtod`. The result is stored in the variable pointed to by `result`.

7. Conversion errors are checked:
   - If `errno` is set to `ERANGE` and the result is `HUGE_VAL` or `-HUGE_VAL`, or if `errno` is nonzero and the result is zero, an error message is printed using `perror`, and the function returns `false`.

8. The function checks if the conversion succeeded and if the rest of the string is empty (i.e., the entire input was consumed):
   - If true, the function returns `true` indicating a successful input.
   - If false, an error message is printed, and the behavior depends on the value of `retryOnInvalid`:
     - If `retryOnInvalid` is `true`, the user is prompted to retry, and the loop continues.
     - If `retryOnInvalid` is `false`, the function returns `false`.

### Example Usage:

```c
double decimalValue;

// Example 1: Prompt and retry until a valid decimal number is entered
getDecimal("Enter a decimal number", true, &decimalValue, DEFAULT_BUFFER_SIZE);

// Example 2: Prompt only once, check if the entered decimal number is valid
if (getDecimal("Enter a decimal number", false, &decimalValue, DEFAULT_BUFFER_SIZE)) {
    printf("You entered the decimal number: %lf\n", decimalValue);
} else {
    fprintf(stderr, "Error during decimal number input.\n");
}
```

### `bool getInput(const char *prompt, bool retryOnInvalid, char *result, size_t bufferSize)`

This function prompts the user for a string input with the specified prompt, handling input validation and retrying on invalid input if specified.

- Parameters:
  - `prompt`: The prompt to display to the user.
  - `retryOnInvalid`: If true, the function will prompt the user to retry on invalid input.
  - `result`: A character array to store the result of the input (string).
  - `bufferSize`: The size of the input buffer.

### How It Works:

1. The function uses a loop to continually prompt the user for input until a non-empty string is entered or the program encounters an error.

2. The prompt is displayed to the user using `printf`.

3. The input is read from the user using `fgets` and stored in the `result` character array.

4. The function removes the newline character from the end of the string, ensuring a clean input.

5. If the entered string is too long and the newline character is not present at the end of the string (indicating incomplete input), the function clears the input buffer using a loop that consumes characters until a newline or the end of the file is encountered.

6. The function checks if a non-empty string is entered:
   - If true, the function returns `true` indicating a successful input.
   - If false, an error message is printed, and the behavior depends on the value of `retryOnInvalid`:
     - If `retryOnInvalid` is `true`, the user is prompted to retry, and the loop continues.
     - If `retryOnInvalid` is `false`, the function returns `false`.

### Example Usage:

```c
char stringValue[DEFAULT_BUFFER_SIZE];

// Example 1: Prompt and retry until a non-empty string is entered
getInput("Enter a string", true, stringValue, DEFAULT_BUFFER_SIZE);

// Example 2: Prompt only once, check if the entered string is valid
if (getInput("Enter a string", false, stringValue, DEFAULT_BUFFER_SIZE)) {
    printf("You entered the string: %s\n", stringValue);
} else {
    fprintf(stderr, "Error during string input.\n");
}
```

## Input Validation

The library ensures proper input validation, checking for various error conditions such as overflow, underflow, and conversion failures. It also provides the option to retry on invalid input.

## Example Usage

```c
#include <stdio.h>
#include "../lib/input_library.h"

int main() {
    long integerValue;
    double decimalValue;
    char stringValue[DEFAULT_BUFFER_SIZE];

    if (getNumber("Enter an integer", true, &integerValue, DEFAULT_BUFFER_SIZE)) {
        printf("You entered: %ld\n", integerValue);
    }

    if (getDecimal("Enter a decimal", true, &decimalValue, DEFAULT_BUFFER_SIZE)) {
        printf("You entered: %lf\n", decimalValue);
    }

    if (getInput("Enter a string", true, stringValue, DEFAULT_BUFFER_SIZE)) {
        printf("You entered: %s\n", stringValue);
    }

    return 0;
}
