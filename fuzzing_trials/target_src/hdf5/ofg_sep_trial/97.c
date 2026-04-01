#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file in memory using a unique file name
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Unable to create file, exit early
    }

    // Create a dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0; // Unable to create dataspace, exit early
    }

    // Create an attribute
    hid_t attr_id = H5Acreate2(file_id, "fuzz_attr", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0; // Unable to create attribute, exit early
    }

    // Write data to the attribute if size is sufficient
    if (size >= sizeof(int) * 10) {
        H5Awrite(attr_id, H5T_NATIVE_INT, data);
    }

    // Call the function-under-test
    hsize_t storage_size = H5Aget_storage_size(attr_id);

    // Clean up resources
    H5Aclose(attr_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}