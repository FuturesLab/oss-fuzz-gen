#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this header for malloc and free

int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    // Ensure the size is at least 2 to split the input data into two non-null strings
    if (size < 2) return 0;

    // Split the input data into two parts
    size_t mid = size / 2;

    // Allocate memory for the two strings and ensure they are null-terminated
    char *pattern = (char *)malloc(mid + 1);
    char *string = (char *)malloc(size - mid + 1);

    if (pattern == NULL || string == NULL) {
        // Handle memory allocation failure
        free(pattern);
        free(string);
        return 0;
    }

    // Copy data into the allocated memory and null-terminate
    memcpy(pattern, data, mid);
    pattern[mid] = '\0';

    memcpy(string, data + mid, size - mid);
    string[size - mid] = '\0';

    // Call the function-under-test
    int result = sqlite3_strglob(pattern, string);

    // Free allocated memory
    free(pattern);
    free(string);

    return 0;
}