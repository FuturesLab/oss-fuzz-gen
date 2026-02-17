#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Declare and initialize an integer variable to hold the error code
    int error_code = 0;

    // Ensure the size is sufficient to avoid out-of-bounds access
    if (size > 0) {
        // Use the first byte of the input data to set the error code
        error_code = data[0] % SQLITE_OK; // Modulo to keep it within valid range
    }

    // Call the function under test
    const char *error_string = sqlite3_errstr(error_code);

    // Optionally, you can do something with the error string, like printing it
    // However, for fuzzing purposes, we typically don't need to output anything
    // printf("Error Code: %d, Error String: %s\n", error_code, error_string);

    return 0;
}