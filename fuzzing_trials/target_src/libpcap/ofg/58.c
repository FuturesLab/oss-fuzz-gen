#include <stdint.h>
#include <stddef.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int tstamp_type = *(const int *)data;

    // Call the function-under-test
    const char *description = pcap_tstamp_type_val_to_description(tstamp_type);

    // Use the description in some way to prevent compiler optimizations
    if (description != NULL) {
        // Do something trivial with the description
        volatile size_t desc_length = 0;
        while (description[desc_length] != '\0') {
            desc_length++;
        }
    }

    return 0;
}