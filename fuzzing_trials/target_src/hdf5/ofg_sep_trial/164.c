#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    hid_t file_id = -1;
    hid_t group_id = -1;
    char group_name[256];

    // Ensure data is not empty and size is sufficient for a group name
    if (size < 1 || size >= sizeof(group_name)) {
        return 0;
    }

    // Copy data to group_name and ensure it's null-terminated
    memcpy(group_name, data, size);
    group_name[size] = '\0';

    // Create a new HDF5 file to contain the group
    file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    group_id = H5Gcreate2(file_id, group_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Close the group if it was created successfully
    if (group_id >= 0) {
        H5Gclose(group_id);
    }

    // Close the file
    H5Fclose(file_id);

    return 0;
}