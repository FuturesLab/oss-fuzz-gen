#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit
    }

    // Ensure that the data is null-terminated to be used as a string
    char group_name[256];
    size_t copy_size = size < 255 ? size : 255;
    if (size > 0) {
        memcpy(group_name, data, copy_size);
    }
    group_name[copy_size] = '\0';

    // Use the data to call the function-under-test
    hid_t group_id = H5Gcreate2(file_id, group_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Close the group if it was successfully created
    if (group_id >= 0) {
        H5Gclose(group_id);
    }

    // Close the file
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}