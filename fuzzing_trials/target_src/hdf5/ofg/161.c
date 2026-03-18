#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Initialize variables
    herr_t status;
    hid_t file_id;
    H5F_info2_t file_info;

    // Check if the input size is sufficient to create a valid file name
    if (size < 1) {
        return 0;
    }

    // Create a file name from the input data
    char file_name[256];
    size_t file_name_size = (size < 255) ? size : 255;
    for (size_t i = 0; i < file_name_size; i++) {
        file_name[i] = data[i] % 26 + 'A'; // Ensure it's a valid character
    }
    file_name[file_name_size] = '\0';

    // Create a new HDF5 file using the file name
    file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    status = H5Fget_info2(file_id, &file_info);

    // Close the file
    H5Fclose(file_id);

    return 0;
}