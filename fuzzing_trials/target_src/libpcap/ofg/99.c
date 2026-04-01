#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int error_code = *((int*)data);

    // Call the function-under-test
    const char *error_message = pcap_strerror(error_code);

    // Use the error_message in some way to avoid compiler optimizations
    // that might remove the call to pcap_strerror
    if (error_message != NULL) {
        volatile char c = error_message[0];
        (void)c;
    }

    return 0;
}