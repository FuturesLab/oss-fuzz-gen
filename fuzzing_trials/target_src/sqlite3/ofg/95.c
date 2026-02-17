#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Ensure the size is valid for our inputs
    if (size < 1) {
        return 0; // No input to process
    }

    // Allocate and initialize two strings for comparison
    int n = size % 100; // Limit the comparison length to a reasonable size
    char *str1 = (char *)malloc(n + 1);
    char *str2 = (char *)malloc(n + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0; // Memory allocation failed
    }

    // Fill the strings with data from the input
    memcpy(str1, data, n);
    str1[n] = '\0'; // Null-terminate the first string

    memcpy(str2, data, n);
    str2[n] = '\0'; // Null-terminate the second string

    // Call the function under test
    int result = sqlite3_strnicmp(str1, str2, n);

    // Free allocated memory
    free(str1);
    free(str2);

    return result; // Return the result of the comparison
}