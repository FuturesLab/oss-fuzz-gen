#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file in memory using core driver
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create a dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create a dataset
    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Call the function-under-test
    herr_t status = H5Dflush(dataset_id);

    // Cleanup
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}