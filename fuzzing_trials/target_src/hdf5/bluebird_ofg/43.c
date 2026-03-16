#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    hid_t dataset_id;
    herr_t status;

    // Initialize the HDF5 library
    H5open();

    // Create a new HDF5 file to obtain a valid dataset ID
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a simple dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset
    dataset_id = H5Dcreate2(file_id, "dset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Use the input data to write to the dataset if size is sufficient
    if (size >= 10 * sizeof(int)) {
        status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    }

    // Call the function-under-test
    status = H5Drefresh(dataset_id);

    // Clean up resources
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}