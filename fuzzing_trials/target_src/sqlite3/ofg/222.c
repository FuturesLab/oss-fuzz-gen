#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int error_code = *(const int*)data;

    // Call the function-under-test
    const char *error_message = sqlite3_errstr(error_code);

    // Use the error_message to avoid compiler optimizations removing the call
    if (error_message != NULL) {
        // Do something trivial with the error_message
        volatile char first_char = error_message[0];
        (void)first_char; // Prevent unused variable warning
    }

    return 0;
}