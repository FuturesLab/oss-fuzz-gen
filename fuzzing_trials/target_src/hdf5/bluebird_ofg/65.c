#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a dataspace
    hsize_t dims[1] = {10}; // Example dimension
    hid_t space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset
    hid_t dset_id = H5Dcreate(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Write the fuzz input data to the dataset
    // Ensure we do not write more than the dataset size
    size_t num_elements = size / sizeof(int);
    if (num_elements > 10) {
        num_elements = 10;
    }
    int buffer[10] = {0}; // Initialize buffer with zeros
    memcpy(buffer, data, num_elements * sizeof(int));
    herr_t status = H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer);

    // Call the function-under-test
    status = H5Dformat_convert(dset_id);

    // Close resources
    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}