#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    hid_t file_id = -1;

    // Ensure the data size is sufficient to create a file name
    if (size < 5) {
        return 0;
    }

    // Create a simple file name from the input data
    char file_name[6];
    for (size_t i = 0; i < 5; ++i) {
        file_name[i] = data[i] % 26 + 'a'; // Ensure it's a valid character
    }
    file_name[5] = '\0';

    // Create a new HDF5 file using the file name
    file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file
    }

    // Reopen the file using H5Freopen
    hid_t reopened_file_id = H5Freopen(file_id);
    if (reopened_file_id < 0) {
        H5Fclose(file_id);
        return 0; // Failed to reopen file
    }

    // Close both file handles
    H5Fclose(reopened_file_id);
    H5Fclose(file_id);

    return 0;
}