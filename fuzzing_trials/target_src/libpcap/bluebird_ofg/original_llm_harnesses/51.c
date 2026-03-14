#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure that the input size is at least the size of an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int dlt_value;
    memcpy(&dlt_value, data, sizeof(int));

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description(dlt_value);

    // Use the description in some way to avoid optimizing it out
    if (description) {
        // For fuzzing purposes, just check the length
        size_t desc_length = strlen(description);
        (void)desc_length;  // Suppress unused variable warning
    }

    return 0;
}