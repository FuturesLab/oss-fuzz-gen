#include <stdint.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to extract the required parameters
    if (size < sizeof(hid_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract parameters from the input data
    hid_t loc_id;
    unsigned int idx;

    // Copy data to variables, ensuring correct type casting
    memcpy(&loc_id, data, sizeof(hid_t));
    memcpy(&idx, data + sizeof(hid_t), sizeof(unsigned int));

    // Call the function-under-test with the extracted parameters
    hid_t attribute = H5Aopen_idx(loc_id, idx);

    // Close the attribute if it was successfully opened
    if (attribute >= 0) {
        H5Aclose(attribute);
    }

    return 0;
}