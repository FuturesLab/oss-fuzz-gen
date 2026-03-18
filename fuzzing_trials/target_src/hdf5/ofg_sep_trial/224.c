#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // Initialize a valid hid_t value for testing
    hid_t space_id = H5Screate(H5S_SCALAR);
    if (space_id < 0) {
        return 0;
    }

    hid_t attribute_id = H5Acreate2(space_id, "test_attribute", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attribute_id < 0) {
        H5Sclose(space_id);
        return 0;
    }

    // Call the function-under-test
    hid_t type_id = H5Aget_type(attribute_id);

    // Check if the type_id is valid and close it
    if (type_id >= 0) {
        H5Tclose(type_id);
    }

    // Close the attribute and dataspace
    H5Aclose(attribute_id);
    H5Sclose(space_id);

    return 0;
}