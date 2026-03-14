#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to hold at least one integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Allocate memory for an integer array
    int *tstamp_types = (int *)malloc(sizeof(int));
    if (tstamp_types == NULL) {
        return 0;
    }

    // Initialize the integer with data from the input
    *tstamp_types = *(int *)data;

    // Call the function-under-test
    pcap_free_tstamp_types(tstamp_types);

    // Free the allocated memory
    free(tstamp_types);

    return 0;
}