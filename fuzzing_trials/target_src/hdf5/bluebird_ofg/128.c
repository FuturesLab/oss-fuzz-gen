#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id;
    hid_t group_id;
    char *group_name;

    // Ensure data is not empty and size is sufficient
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to work with HDF5
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Allocate memory for group_name and ensure it's null-terminated
    group_name = (char *)malloc(size + 1);
    if (group_name == NULL) {
        H5Fclose(file_id);
        return 0;
    }
    memcpy(group_name, data, size);
    group_name[size] = '\0';

    // Create a group to ensure it exists
    group_id = H5Gcreate1(file_id, group_name, 0);
    if (group_id >= 0) {
        H5Gclose(group_id);
    }

    // Call the function-under-test
    group_id = H5Gopen1(file_id, group_name);

    // Clean up
    if (group_id >= 0) {
        H5Gclose(group_id);
    }
    H5Fclose(file_id);
    free(group_name);

    return 0;
}