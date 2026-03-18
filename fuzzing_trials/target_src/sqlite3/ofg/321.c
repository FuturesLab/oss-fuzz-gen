#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_321(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to split into two strings
    if (size < 2) {
        return 0;
    }

    // Find a midpoint to split the input data into two strings
    size_t midpoint = size / 2;

    // Allocate memory for the two strings and ensure they are null-terminated
    char *str1 = (char *)malloc(midpoint + 1);
    char *str2 = (char *)malloc(size - midpoint + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, midpoint);
    str1[midpoint] = '\0';

    memcpy(str2, data + midpoint, size - midpoint);
    str2[size - midpoint] = '\0';

    // Call the function under test
    int result = sqlite3_strglob(str1, str2);

    // Free allocated memory
    free(str1);
    free(str2);

    return 0;
}