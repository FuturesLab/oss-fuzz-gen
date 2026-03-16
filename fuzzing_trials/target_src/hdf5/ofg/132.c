#include <stdint.h>
#include <hdf5.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Initialize variables for H5Dcreate2 parameters
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Ensure the dataset name is null-terminated and not empty
    char dataset_name[256];
    size_t name_len = size < 255 ? size : 255;
    memcpy(dataset_name, data, name_len);
    dataset_name[name_len] = '\0';

    // Create a simple dataspace
    hsize_t dims[2] = {10, 10};
    hid_t dataspace_id = H5Screate_simple(2, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Use default property lists
    hid_t dcpl_id = H5P_DEFAULT;
    hid_t dapl_id = H5P_DEFAULT;
    hid_t lcpl_id = H5P_DEFAULT;

    // Create a dataset using H5Dcreate2
    hid_t dataset_id = H5Dcreate2(file_id, dataset_name, H5T_NATIVE_INT, dataspace_id, lcpl_id, dcpl_id, dapl_id);

    // Close resources
    if (dataset_id >= 0) H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    return 0;
}