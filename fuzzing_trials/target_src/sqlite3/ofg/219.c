#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    int error_code;

    // Ensure we have at least 4 bytes to create an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Copy the first 4 bytes from data to form an integer error code
    error_code = *(const int *)data;

    // Call the function-under-test
    const char *error_message = sqlite3_errstr(error_code);

    // Use the error_message in some way to avoid compiler optimizations
    // that might remove the call. Here, we just check if it's not NULL.
    if (error_message != NULL) {
        // Do something with error_message if needed
    }

    return 0;
}