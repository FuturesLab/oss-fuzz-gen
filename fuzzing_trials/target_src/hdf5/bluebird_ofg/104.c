#include <stdint.h>
#include <stdlib.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for an hid_t and five unsigned int variables
    if (size < sizeof(hid_t) + 5 * sizeof(unsigned int)) {
        return 0;
    }

    // Initialize the variables
    hid_t file_id = *((hid_t *)data);
    unsigned int accesses = 0;
    unsigned int hits = 0;
    unsigned int misses = 0;
    unsigned int evictions = 0;
    unsigned int bypasses = 0;

    // Call the function-under-test
    herr_t result = H5Fget_page_buffering_stats(file_id, &accesses, &hits, &misses, &evictions, &bypasses);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result < 0) {
        // Handle error (for fuzzing, we might simply ignore it)
    }

    return 0;
}