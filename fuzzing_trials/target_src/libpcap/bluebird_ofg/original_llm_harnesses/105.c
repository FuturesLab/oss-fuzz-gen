#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int dlt_value = *(const int *)data;

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description_or_dlt(dlt_value);

    // Use the result to avoid compiler optimizations removing the function call
    if (description != NULL) {
        // Do something trivial with the description
        (void)description;
    }

    return 0;
}