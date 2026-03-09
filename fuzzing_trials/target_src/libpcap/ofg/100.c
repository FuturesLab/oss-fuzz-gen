#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    int error_code = 0;

    // Ensure we have enough data to extract an integer
    if (size >= sizeof(int)) {
        // Extract an integer from the data
        error_code = *((int*)data);
    }

    // Call the function-under-test
    const char *error_message = pcap_strerror(error_code);

    // Use the error_message in some way to prevent compiler optimizations
    if (error_message != NULL) {
        volatile const char *msg = error_message;
        (void)msg;
    }

    return 0;
}