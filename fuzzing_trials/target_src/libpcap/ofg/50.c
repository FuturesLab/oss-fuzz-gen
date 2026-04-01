#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int val = *(const int *)data;

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description(val);

    // Use the description in some way to avoid compiler optimizations
    if (description != NULL) {
        // For example, just check the length of the string
        volatile size_t len = strlen(description);
        (void)len; // Suppress unused variable warning
    }

    return 0;
}