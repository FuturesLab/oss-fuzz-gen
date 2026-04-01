#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include the standard library for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_405(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to create two strings
    if (size < 2) {
        return 0;
    }

    // Find a midpoint to split the data into two strings
    size_t midpoint = size / 2;

    // Create two null-terminated strings from the input data
    char *str1 = (char *)malloc(midpoint + 1);
    char *str2 = (char *)malloc(size - midpoint + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0;
    }

    memcpy(str1, data, midpoint);
    str1[midpoint] = '\0';

    memcpy(str2, data + midpoint, size - midpoint);
    str2[size - midpoint] = '\0';

    // Call the function-under-test
    int result = sqlite3_stricmp(str1, str2);

    // Clean up
    free(str1);
    free(str2);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}