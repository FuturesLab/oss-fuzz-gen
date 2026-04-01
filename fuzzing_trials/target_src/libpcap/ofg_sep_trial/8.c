#include <stdint.h>
#include <stddef.h>
#include <pcap.h>
#include <string.h> // Include for strlen

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure size is at least 4 bytes to read an integer
    if (size < 4) {
        return 0;
    }

    // Read the first 4 bytes of data as an integer
    int dlt_value = *((const int *)data);

    // Call the function-under-test
    const char *dlt_name = pcap_datalink_val_to_name(dlt_value);

    // Use the result to avoid optimization out
    if (dlt_name != NULL) {
        // Do something trivial with dlt_name
        volatile size_t len = strlen(dlt_name);
        (void)len;
    }

    return 0;
}