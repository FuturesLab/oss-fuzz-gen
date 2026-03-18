#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Initialize variables for H5Acreate1 parameters
    hid_t loc_id = H5P_DEFAULT;  // Using default property list
    const char *attr_name = "fuzz_attribute";  // Non-NULL attribute name
    hid_t type_id = H5T_NATIVE_INT;  // Using native integer type
    hid_t space_id = H5Screate(H5S_SCALAR);  // Create a scalar dataspace
    hid_t acpl_id = H5P_DEFAULT;  // Using default attribute creation property list

    // Call the function-under-test
    hid_t attr_id = H5Acreate1(loc_id, attr_name, type_id, space_id, acpl_id);

    // Clean up resources
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }
    if (space_id >= 0) {
        H5Sclose(space_id);
    }

    return 0;
}