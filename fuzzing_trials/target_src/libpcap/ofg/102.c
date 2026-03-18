#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for at least one integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Allocate memory for an integer array
    int *tstamp_types = (int *)malloc(sizeof(int) * (size / sizeof(int)));
    if (tstamp_types == NULL) {
        return 0;
    }

    // Copy the data into the integer array
    for (size_t i = 0; i < size / sizeof(int); ++i) {
        tstamp_types[i] = ((int *)data)[i];
    }

    // Call the function-under-test
    pcap_free_tstamp_types(tstamp_types);

    // Free the allocated memory
    free(tstamp_types);

    return 0;
}