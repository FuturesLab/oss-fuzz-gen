#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    // Ensure that the input size is at least the size of an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Cast the input data to an integer
    int error_code = *(const int *)data;

    // Call the function-under-test
    const char *error_message = sqlite3_errstr(error_code);

    // Optionally print the error message for debugging purposes
    if (error_message != NULL) {
        printf("Error message: %s\n", error_message);
    }

    return 0;
}