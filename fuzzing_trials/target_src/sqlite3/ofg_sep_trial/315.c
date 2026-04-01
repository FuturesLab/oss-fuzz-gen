#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_315(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to split into two non-null strings
    if (size < 2) {
        return 0;
    }

    // Find a suitable split point for the input data
    size_t split_point = size / 2;

    // Create two null-terminated strings from the input data
    char *pattern = (char *)malloc(split_point + 1);
    char *string = (char *)malloc(size - split_point + 1);

    if (pattern == NULL || string == NULL) {
        free(pattern);
        free(string);
        return 0;
    }

    // Copy data into the two strings
    memcpy(pattern, data, split_point);
    pattern[split_point] = '\0';

    memcpy(string, data + split_point, size - split_point);
    string[size - split_point] = '\0';

    // Call the function-under-test
    int result = sqlite3_strglob(pattern, string);

    // Clean up
    free(pattern);
    free(string);

    return 0;
}