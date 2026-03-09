#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure that size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Use the first bytes of data to form an integer error code
    int error_code = *(const int*)data;

    // Call the function-under-test
    const char *error_message = pcap_strerror(error_code);

    // Use the error_message in some way to prevent it from being optimized out
    if (error_message) {
        volatile const char *temp = error_message;
        (void)temp;
    }

    return 0;
}