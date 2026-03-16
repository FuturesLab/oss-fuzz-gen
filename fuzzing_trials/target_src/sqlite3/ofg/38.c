#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to split into two non-null strings
    if (size < 4) {
        return 0;
    }

    // Find a position to split the data into two strings
    size_t split_pos = size / 2;

    // Allocate buffers dynamically to avoid stack overflow
    char *uri = (char *)malloc(split_pos + 1);
    char *param = (char *)malloc(size - split_pos + 1);

    if (uri == NULL || param == NULL) {
        free(uri);
        free(param);
        return 0;
    }

    // Use memcpy safely by ensuring the split_pos is within bounds
    memcpy(uri, data, split_pos);
    uri[split_pos] = '\0';

    memcpy(param, data + split_pos, size - split_pos);
    param[size - split_pos] = '\0';

    // Ensure the URI is a valid URI format that sqlite3_uri_parameter can process
    if (strstr(uri, "file:") != uri) {
        free(uri);
        free(param);
        return 0;
    }

    // Call the function-under-test
    const char *result = sqlite3_uri_parameter(uri, param);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        volatile char c = result[0];
        (void)c;
    }

    // Free allocated memory
    free(uri);
    free(param);

    return 0;
}