#include <stdint.h>
#include <stddef.h>
#include "pcap/pcap.h"

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    int dlt_value = 0;

    if (size >= sizeof(int)) {
        // Use the first four bytes of data as an integer value for dlt_value
        dlt_value = *(const int *)data;
    }

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description_or_dlt(dlt_value);

    // Use the description in some way to prevent compiler optimizations from removing the call
    if (description != NULL) {
        // Print the description to a volatile variable to prevent optimization
        volatile const char *volatile_description = description;
        (void)volatile_description;
    }

    return 0;
}