#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

// Declare the function-under-test
Janet janet_dyn(const char *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_342(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to be used as a string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data and null-terminate it
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    Janet result = janet_dyn(null_terminated_data);

    // Free the allocated memory
    free(null_terminated_data);

    // Return 0 to indicate the fuzzer can continue
    return 0;
}