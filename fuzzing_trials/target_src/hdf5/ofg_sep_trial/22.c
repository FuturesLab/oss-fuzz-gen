#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t loc_id = H5P_DEFAULT;  // Use a default property list
    const char *attr_name = "fuzz_attribute";
    hid_t type_id = H5T_NATIVE_INT;  // Use a native integer type
    hid_t space_id = H5S_SCALAR;  // Use a scalar dataspace
    hid_t acpl_id = H5P_DEFAULT;  // Use a default attribute creation property list
    hid_t aapl_id = H5P_DEFAULT;  // Use a default attribute access property list

    // Ensure that the data is not NULL and size is non-zero
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a new HDF5 file to use as the location ID
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }
    loc_id = file_id;

    // Call the function-under-test
    hid_t attr_id = H5Acreate2(loc_id, attr_name, type_id, space_id, acpl_id, aapl_id);

    // Close the attribute and file to clean up
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }
    H5Fclose(file_id);

    return 0;
}