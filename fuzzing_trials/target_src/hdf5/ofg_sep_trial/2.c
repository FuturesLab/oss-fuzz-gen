#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain at least one character for the group name
    if (size < 1) {
        return 0;
    }

    // Initialize the HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a group in the file
    hid_t group_id = H5Gcreate(file_id, "/fuzz_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Close the group
    H5Gclose(group_id);

    // Use the first part of the data as a group name
    char group_name[256];
    size_t group_name_length = size < 255 ? size : 255;
    memcpy(group_name, data, group_name_length);
    group_name[group_name_length] = '\0';

    // Call the function-under-test
    hid_t opened_group_id = H5Gopen1(file_id, group_name);

    // Check if the group was opened successfully
    if (opened_group_id >= 0) {
        H5Gclose(opened_group_id);
    }

    // Close the file
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}