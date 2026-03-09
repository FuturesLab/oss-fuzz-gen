#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <magic.h>
#include <string.h>

extern "C" {
    // Include the necessary headers for the function-under-test
    #include "magic.h"
}

// Fuzzing harness for magic_getparam
extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct magic_set *ms;
    int param;
    void *value;
    int result;

    // Initialize the magic_set structure
    ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0; // Return if magic_open fails
    }

    // Load a magic database (this is necessary for magic_set to function properly)
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0; // Return if magic_load fails
    }

    // Ensure the size is sufficient to extract an integer for param
    if (size < sizeof(int)) {
        magic_close(ms);
        return 0;
    }

    // Extract an integer from the data to use as the parameter
    param = *(reinterpret_cast<const int*>(data));

    // Allocate memory for the value pointer
    value = malloc(256); // Allocate a buffer for the value
    if (value == NULL) {
        magic_close(ms);
        return 0; // Return if memory allocation fails
    }

    // Initialize the allocated memory to ensure it's not null
    memset(value, 0, 256);

    // Call the function-under-test
    result = magic_getparam(ms, param, value);

    // Check the result to ensure the function-under-test is being utilized
    if (result == -1) {
        // Handle error if needed
    }

    // Free allocated resources
    free(value);
    magic_close(ms);

    return 0;
}