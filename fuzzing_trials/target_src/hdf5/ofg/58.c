#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dapl_id = H5Pcreate(H5P_DATASET_ACCESS);

    // Ensure that the dataset name is null-terminated
    char dataset_name[256];
    size_t name_length = size < 255 ? size : 255;
    memcpy(dataset_name, data, name_length);
    dataset_name[name_length] = '\0';

    // Call the function-under-test
    hid_t dataset_id = H5Dopen2(file_id, dataset_name, dapl_id);

    // Clean up resources
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }
    H5Pclose(dapl_id);
    H5Fclose(file_id);

    return 0;
}