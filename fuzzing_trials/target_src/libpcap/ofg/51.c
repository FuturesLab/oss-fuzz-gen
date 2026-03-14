#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int datalink_val = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        datalink_val |= ((int)data[i]) << (i * 8);
    }

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description(datalink_val);

    // Use the description in some way to ensure it's not optimized out
    if (description != NULL) {
        // Simply print the description length, for example
        volatile size_t desc_len = 0;
        while (description[desc_len] != '\0') {
            ++desc_len;
        }
    }

    return 0;
}