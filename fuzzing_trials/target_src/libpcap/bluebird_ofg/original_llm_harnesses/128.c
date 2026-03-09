#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure that size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int tstamp_type = *(const int *)data;

    // Call the function-under-test
    const char *result = pcap_tstamp_type_val_to_name(tstamp_type);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Do something trivial with the result
        volatile size_t len = 0;
        while (result[len] != '\0') {
            len++;
        }
    }

    return 0;
}