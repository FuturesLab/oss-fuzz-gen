#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a new HDF5 file using default properties
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit early
    }

    // Create a dataspace for the attribute
    hsize_t dims[1] = {1};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0; // Failed to create dataspace, exit early
    }

    // Create an attribute
    hid_t attr_id = H5Acreate2(file_id, "fuzz_attr", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0; // Failed to create attribute, exit early
    }

    // Call the function-under-test
    herr_t status = H5Aclose(attr_id);

    // Cleanup
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Return 0 to indicate the fuzzer can continue
    return 0;
}