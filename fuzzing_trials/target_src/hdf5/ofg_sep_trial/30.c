#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to extract parameters
    if (size < sizeof(hid_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract parameters from the data
    hid_t loc_id = *((hid_t *)data);
    unsigned int idx = *((unsigned int *)(data + sizeof(hid_t)));

    // Call the function-under-test
    hid_t attribute_id = H5Aopen_idx(loc_id, idx);

    // If the attribute was successfully opened, close it
    if (attribute_id >= 0) {
        H5Aclose(attribute_id);
    }

    return 0;
}