#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the string.h library for memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create an hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t from the input data
    hid_t attribute_id;
    memcpy(&attribute_id, data, sizeof(hid_t));

    // Call the function-under-test
    hid_t dataspace_id = H5Aget_space(attribute_id);

    // Close the dataspace if it was successfully created
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    return 0;
}