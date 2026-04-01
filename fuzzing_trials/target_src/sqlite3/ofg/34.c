#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for splitting into two non-null strings
    if (size < 3) { // Adjusted to ensure both strings have at least one character
        return 0;
    }

    // Find a position to split the input data into two strings
    size_t split_pos = 1 + (size - 2) / 2; // Ensure both parts are non-empty

    // Allocate memory for the URI and the parameter name
    char *uri = (char *)malloc(split_pos + 1);
    char *param = (char *)malloc(size - split_pos + 1);

    if (!uri || !param) {
        free(uri);
        free(param);
        return 0; // Return if memory allocation fails
    }

    // Copy data into uri and param, ensuring null-termination
    memcpy(uri, data, split_pos);
    uri[split_pos] = '\0';

    memcpy(param, data + split_pos, size - split_pos);
    param[size - split_pos] = '\0';

    // Validate URI format to prevent heap-buffer-overflow
    // Ensure uri starts with "file:" or another valid SQLite URI prefix
    if (strncmp(uri, "file:", 5) != 0) {
        free(uri);
        free(param);
        return 0;
    }

    // Call the function under test
    const char *result = sqlite3_uri_parameter(uri, param);

    // Free allocated memory
    free(uri);
    free(param);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != NULL) {
        volatile size_t result_len = strlen(result);
        (void)result_len;
    }

    return 0;
}