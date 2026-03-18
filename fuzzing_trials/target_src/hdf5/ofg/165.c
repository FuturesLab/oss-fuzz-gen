#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    hid_t file_id;
    hid_t group_id;
    char group_name[256];
    size_t name_len;

    // Ensure we have enough data to work with
    if (size < 2) {
        return 0;
    }

    // Open a new HDF5 file to work with
    file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Copy data to group_name ensuring null-termination
    name_len = size < 255 ? size : 255;
    memcpy(group_name, data, name_len);
    group_name[name_len] = '\0';

    // Call the function-under-test
    group_id = H5Gcreate1(file_id, group_name, name_len);

    // Close the group and file if they were successfully created
    if (group_id >= 0) {
        H5Gclose(group_id);
    }
    H5Fclose(file_id);

    return 0;
}