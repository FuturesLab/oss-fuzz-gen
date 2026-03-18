#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file and an attribute to read
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    hid_t attr_id = H5Acreate2(file_id, "attr", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);

    // Prepare a buffer to read into
    int read_data;
    
    // Ensure data is not NULL and size is sufficient
    if (data != NULL && size >= sizeof(int)) {
        // Call the function-under-test
        herr_t status = H5Aread(attr_id, H5T_NATIVE_INT, &read_data);
    }

    // Clean up
    H5Aclose(attr_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}