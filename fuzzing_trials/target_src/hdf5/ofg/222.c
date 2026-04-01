#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    hsize_t filesize;
    herr_t status;

    // Create a temporary file for testing
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit early
    }

    // Simulate writing data to the file to ensure it's not empty
    if (size > 0) {
        hid_t dataspace_id = H5Screate_simple(1, &size, NULL);
        hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_UINT8, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
    }

    // Call the function-under-test
    status = H5Fget_filesize(file_id, &filesize);

    // Close the file
    H5Fclose(file_id);

    // Return success
    return 0;
}