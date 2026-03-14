#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int tstamp_type = *(const int *)data;

    // Call the function-under-test
    const char *description = pcap_tstamp_type_val_to_description(tstamp_type);

    // Use the description to prevent compiler optimizations from removing the call
    if (description != NULL) {
        volatile char dummy;
        dummy = description[0];
    }

    return 0;
}