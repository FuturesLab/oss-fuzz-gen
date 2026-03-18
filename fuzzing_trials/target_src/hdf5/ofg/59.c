#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize an HDF5 file
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

    // Create a dataset
    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Fuzzing the function-under-test
    hid_t access_plist_id = H5Dget_access_plist(dataset_id);

    // Clean up
    H5Pclose(access_plist_id);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    return 0;
}