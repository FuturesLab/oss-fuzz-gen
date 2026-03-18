#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include stdlib.h for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to split into two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Find a midpoint to split the data into two parts
    size_t midpoint = size / 2;

    // Allocate memory for the URI and parameter strings
    char *uri = (char *)malloc(midpoint + 1);
    char *param = (char *)malloc(size - midpoint + 1);

    // Ensure memory allocation was successful
    if (uri == NULL || param == NULL) {
        free(uri);
        free(param);
        return 0;
    }

    // Copy the data into the URI and parameter strings and null-terminate them
    memcpy(uri, data, midpoint);
    uri[midpoint] = '\0';

    memcpy(param, data + midpoint, size - midpoint);
    param[size - midpoint] = '\0';

    // Ensure the URI is a valid URI format for sqlite3_uri_parameter
    // Typically, the URI should start with "file:" or similar schema
    if (strncmp(uri, "file:", 5) != 0) {
        free(uri);
        free(param);
        return 0;
    }

    // Call the function-under-test
    const char *result = sqlite3_uri_parameter(uri, param);

    // Use the result in some way to prevent the compiler from optimizing it away
    if (result != NULL) {
        volatile char first_char = result[0];
        (void)first_char; // Suppress unused variable warning
    }

    // Free the allocated memory
    free(uri);
    free(param);

    return 0;
}