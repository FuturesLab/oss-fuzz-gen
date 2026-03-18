#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_403(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create two non-null strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for two strings
    size_t mid = size / 2;

    // Allocate memory for the two strings and ensure null-termination
    char *str1 = (char *)malloc(mid + 1);
    char *str2 = (char *)malloc(size - mid + 1);

    if (str1 == NULL || str2 == NULL) {
        // Handle memory allocation failure
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, mid);
    str1[mid] = '\0';

    memcpy(str2, data + mid, size - mid);
    str2[size - mid] = '\0';

    // Call the function-under-test
    int result = sqlite3_stricmp(str1, str2);

    // Clean up allocated memory
    free(str1);
    free(str2);

    return 0;
}