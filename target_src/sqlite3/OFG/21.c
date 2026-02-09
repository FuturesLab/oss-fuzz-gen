#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure that the input size is within the range of valid SQLite error codes
    int error_code;

    // Initialize error_code based on the input data
    if (size < sizeof(int)) {
        error_code = 0; // Default to a known error code if the input is too small
    } else {
        // Use the first 4 bytes of the input data to set the error code
        error_code = *((const int *)data) % (SQLITE_CONSTRAINT + 1); // Limit to valid error codes
    }

    // Call the function under test
    const char *error_string = sqlite3_errstr(error_code);

    // Optionally, you could do something with error_string here, like logging or checking
    // However, we are primarily focused on calling the function

    return 0;
}