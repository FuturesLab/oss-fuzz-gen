#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Interpret the first bytes of data as a hid_t
    hid_t attribute_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t dataspace_id = H5Aget_space(attribute_id);

    // Close the dataspace if it is valid
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    return 0;
}