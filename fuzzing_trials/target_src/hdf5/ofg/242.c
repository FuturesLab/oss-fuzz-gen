#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Convert data to a C-style string
    char filename[256];
    size_t filename_len = size < 255 ? size : 255;
    for (size_t i = 0; i < filename_len; i++) {
        filename[i] = (char)data[i];
    }
    filename[filename_len] = '\0';

    // Set up other parameters for H5Fcreate
    unsigned int flags = H5F_ACC_TRUNC; // Use a valid flag
    hid_t fcpl_id = H5P_DEFAULT; // Use default file creation property list
    hid_t fapl_id = H5P_DEFAULT; // Use default file access property list

    // Call the function-under-test
    hid_t file_id = H5Fcreate(filename, flags, fcpl_id, fapl_id);

    // Clean up: close the file if it was created successfully
    if (file_id >= 0) {
        H5Fclose(file_id);
    }

    return 0;
}