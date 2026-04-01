#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Declare and initialize the hid_t variable
    hid_t attribute_id = 0;

    // Ensure that size is sufficient to extract a valid hid_t
    if (size >= sizeof(hid_t)) {
        // Extract a hid_t from the input data
        attribute_id = *(const hid_t *)data;
    }

    // Call the function-under-test
    hid_t dataspace_id = H5Aget_space(attribute_id);

    // Close the dataspace if it was successfully opened
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    return 0;
}