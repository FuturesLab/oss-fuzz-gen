#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include stdlib.h for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Ensure the size is at least 1 for the strings and the comparison length
    if (size < 1) {
        return 0;
    }

    // Allocate memory for two strings and the comparison length
    int comparison_length = size > 100 ? 100 : (int)size; // Limit comparison length to 100
    char *str1 = (char *)malloc(size + 1);
    char *str2 = (char *)malloc(size + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0; // Memory allocation failed
    }

    // Fill str1 and str2 with data from the input
    memcpy(str1, data, size);
    str1[size] = '\0'; // Null-terminate the first string

    memcpy(str2, data, size);
    str2[size] = '\0'; // Null-terminate the second string

    // Call the function under test
    int result = sqlite3_strnicmp(str1, str2, comparison_length);

    // Free allocated memory
    free(str1);
    free(str2);

    return result;
}