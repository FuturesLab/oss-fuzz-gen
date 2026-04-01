#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a memory file to simulate a dataset
    hid_t file_id = H5Fcreate("temp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Define dataspace dimensions
    hsize_t dims[1] = {10}; // Example dimension size
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset
    hid_t dataset_id = H5Dcreate(file_id, "dataset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Call the function-under-test
    hsize_t storage_size = H5Dget_storage_size(dataset_id);

    // Print the storage size for debugging purposes
    printf("Storage size: %llu\n", (unsigned long long)storage_size);

    // Clean up resources
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}