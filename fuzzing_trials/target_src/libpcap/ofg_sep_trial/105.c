#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    int dlt;

    // Ensure the input size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Use the first 4 bytes of data as an int for the dlt value
    dlt = *(const int *)data;

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description_or_dlt(dlt);

    // Use the description in some way to ensure it is accessed
    // For fuzzing purposes, we can just check if it's not NULL
    if (description != NULL) {
        // Do something with the description if needed
    }

    return 0;
}