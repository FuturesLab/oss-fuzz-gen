#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize an integer from the input data
    int *tstamp_types = (int *)malloc(sizeof(int));
    if (tstamp_types == NULL) {
        return 0;
    }

    // Copy data into the integer
    *tstamp_types = *(int *)data;

    // Call the function-under-test
    pcap_free_tstamp_types(tstamp_types);

    // Free the allocated memory
    free(tstamp_types);

    return 0;
}