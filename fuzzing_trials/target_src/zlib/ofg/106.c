#include <stdint.h>
#include <stddef.h>
#include <zlib.h>  // Include the zlib header for the zError function

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    int error_code;

    // Ensure we have at least 4 bytes to form an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Copy the first 4 bytes from data into error_code
    error_code = *((int*)data);

    // Call the zError function with the error_code
    const char *error_message = zError(error_code);

    // Use the error_message to prevent compiler optimizations
    if (error_message != NULL) {
        // Do something trivial with error_message
        volatile const char *temp = error_message;
        (void)temp;
    }

    return 0;
}