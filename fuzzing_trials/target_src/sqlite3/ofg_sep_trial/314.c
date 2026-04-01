#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include the stdlib.h for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_314(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Find a position to split the data into two strings
    size_t split_pos = size / 2;

    // Create two null-terminated strings from the input data
    char *pattern = (char *)malloc(split_pos + 1);
    char *string = (char *)malloc(size - split_pos + 1);

    if (pattern == NULL || string == NULL) {
        free(pattern);
        free(string);
        return 0;
    }

    memcpy(pattern, data, split_pos);
    pattern[split_pos] = '\0';

    memcpy(string, data + split_pos, size - split_pos);
    string[size - split_pos] = '\0';

    // Call the function-under-test
    int result = sqlite3_strglob(pattern, string);

    // Clean up
    free(pattern);
    free(string);

    return 0;
}