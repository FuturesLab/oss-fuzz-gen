#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract parameters
    if (size < sizeof(hid_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract parameters from the input data
    hid_t loc_id = *((hid_t *)data);
    unsigned int idx = *((unsigned int *)(data + sizeof(hid_t)));

    // Call the function-under-test
    hid_t attribute_id = H5Aopen_idx(loc_id, idx);

    // Close the attribute if it was successfully opened
    if (attribute_id >= 0) {
        H5Aclose(attribute_id);
    }

    return 0;
}