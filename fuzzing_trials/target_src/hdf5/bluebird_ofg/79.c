#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for the fuzzer
    if (size < 2) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a file and a group to ensure we have a valid hid_t
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }
    
    hid_t group_id = H5Gcreate2(file_id, "/test_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Close the group to prepare for unlinking
    H5Gclose(group_id);

    // Prepare the group name from the input data
    size_t name_len = size - 1;
    char *group_name = (char *)malloc(name_len + 1);
    if (group_name == NULL) {
        H5Fclose(file_id);
        return 0;
    }
    memcpy(group_name, data, name_len);
    group_name[name_len] = '\0';

    // Call the function-under-test
    H5Gunlink(file_id, group_name);

    // Clean up
    free(group_name);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}