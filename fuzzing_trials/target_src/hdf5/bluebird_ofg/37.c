#include <stdint.h>
#include <stdlib.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file using the default properties.
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file
    }

    // Create a dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0; // Failed to create dataspace
    }

    // Create a dataset
    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0; // Failed to create dataset
    }

    // Close the dataset and dataspace
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // Prepare parameters for H5Fget_vfd_handle
    void *file_handle = NULL;
    hid_t fapl_id = H5P_DEFAULT;

    // Call the function under test
    herr_t status = H5Fget_vfd_handle(file_id, fapl_id, &file_handle);

    // Clean up and close the file
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}