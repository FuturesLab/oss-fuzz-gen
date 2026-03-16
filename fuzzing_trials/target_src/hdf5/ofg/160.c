#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    hid_t file_id;
    H5F_info2_t file_info;
    herr_t status;

    // Ensure that the size is large enough to contain a valid file name
    if (size < 1) {
        return 0;
    }

    // Create a temporary file name from the input data
    char file_name[256];
    size_t file_name_length = size < 255 ? size : 255;
    for (size_t i = 0; i < file_name_length; i++) {
        file_name[i] = data[i] % 26 + 'A';  // Convert to a valid character
    }
    file_name[file_name_length] = '\0';

    // Create a new HDF5 file using the generated file name
    file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;  // Failed to create file, exit
    }

    // Call the function-under-test
    status = H5Fget_info2(file_id, &file_info);

    // Close the file
    H5Fclose(file_id);

    return 0;
}