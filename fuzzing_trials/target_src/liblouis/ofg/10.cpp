#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    // Include the actual header for lou_findTable
    #include "/src/liblouis/liblouis/liblouis.h"
}

// Fuzzer entry point
extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }

    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the input

    // Call the function-under-test
    char *result = lou_findTable(input);

    // Free the memory allocated for the input
    free(input);

    // If result is non-NULL, free the result as well
    if (result != NULL) {
        free(result);
    }

    return 0;
}