#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  // Include for uint8_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    // Ensure the input size is reasonable for a format string
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Allocate memory for the format string
    char *formatString = (char *)malloc(size + 1);
    if (formatString == NULL) {
        return 0; // Memory allocation failed
    }

    // Copy the input data to the format string and null-terminate it
    memcpy(formatString, data, size);
    formatString[size] = '\0';

    // Call the function under test
    char *result = sqlite3_mprintf(formatString, NULL);

    // Free the allocated format string
    free(formatString);

    // Free the result from sqlite3_mprintf if it is not NULL
    if (result != NULL) {
        sqlite3_free(result);
    }

    return 0;
}