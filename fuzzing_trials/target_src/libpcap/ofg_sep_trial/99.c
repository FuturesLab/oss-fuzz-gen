#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Initialize an integer from the input data
    int error_code = 0;
    if (size >= sizeof(int)) {
        error_code = *(const int*)data;
    }

    // Call the function-under-test
    const char *error_message = pcap_strerror(error_code);

    // Use the error_message to avoid compiler optimizations that might skip the call
    if (error_message != NULL) {
        // Print the error message length (not the message itself to avoid output clutter)
        size_t length = 0;
        while (error_message[length] != '\0') {
            length++;
        }
    }

    return 0;
}