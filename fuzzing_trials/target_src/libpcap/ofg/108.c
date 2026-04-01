#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int status_code = *(const int *)data;

    // Call the function-under-test
    const char *result = pcap_statustostr(status_code);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Do something trivial with the result
        volatile char first_char = result[0];
        (void)first_char;
    }

    return 0;
}