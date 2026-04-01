#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute
    hid_t attr_id = H5Acreate2(file_id, "test_attribute", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Close the attribute
    H5Aclose(attr_id);

    // Ensure the input data is null-terminated for use as a string
    char attribute_name[256];
    size_t copy_size = size < 255 ? size : 255;
    memcpy(attribute_name, data, copy_size);
    attribute_name[copy_size] = '\0';

    // Call the function-under-test
    H5Adelete(file_id, attribute_name);

    // Clean up
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}