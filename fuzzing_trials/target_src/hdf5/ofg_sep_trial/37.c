#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    hid_t file_id;
    herr_t status;
    char group_name[256];

    // Ensure the data is not empty and can be used as a group name
    if (size == 0 || size > 255) {
        return 0;
    }

    // Copy data into group_name and ensure it is null-terminated
    memcpy(group_name, data, size);
    group_name[size] = '\0';

    // Create a new HDF5 file to work with
    file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a group in the file
    hid_t group_id = H5Gcreate(file_id, group_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Close the group
    H5Gclose(group_id);

    // Fuzz the H5Ldelete function
    status = H5Ldelete(file_id, group_name, H5P_DEFAULT);

    // Close the file
    H5Fclose(file_id);

    return 0;
}