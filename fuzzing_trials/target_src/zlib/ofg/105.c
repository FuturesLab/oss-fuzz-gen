#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int error_code = *((int *)data);

    // Call the function-under-test
    const char *error_message = zError(error_code);

    // Use the error message in some way to prevent compiler optimizations
    if (error_message != NULL) {
        // For fuzzing purposes, we don't need to do anything with the message
    }

    return 0;
}