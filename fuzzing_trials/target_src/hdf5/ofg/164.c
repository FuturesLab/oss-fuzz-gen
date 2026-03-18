#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid input
    if (size < 1) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Use the input data to create a group name
    char group_name[256];
    size_t name_length = size < 255 ? size : 255;
    for (size_t i = 0; i < name_length; ++i) {
        group_name[i] = data[i] % 26 + 'A'; // Ensure it's a valid character
    }
    group_name[name_length] = '\0';

    // Call the function-under-test
    hid_t group_id = H5Gcreate1(file_id, group_name, name_length);

    // Close the group and file
    if (group_id >= 0) {
        H5Gclose(group_id);
    }
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}