#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for a null-terminated string
    if (size < 2) {
        return 0;
    }

    // Create a copy of the data and ensure it is null-terminated
    char *group_name = (char *)malloc(size + 1);
    if (group_name == NULL) {
        return 0;
    }
    memcpy(group_name, data, size);
    group_name[size] = '\0';

    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        free(group_name);
        H5close();
        return 0;
    }

    // Ensure the group name is valid by replacing any invalid characters
    for (size_t i = 0; i < size; i++) {
        // Replace non-alphanumeric characters with '_'
        if (!((group_name[i] >= 'a' && group_name[i] <= 'z') ||
              (group_name[i] >= 'A' && group_name[i] <= 'Z') ||
              (group_name[i] >= '0' && group_name[i] <= '9'))) {
            group_name[i] = '_';
        }
    }

    // Create a group to ensure it exists for opening
    hid_t group_id = H5Gcreate1(file_id, group_name, 0);
    if (group_id >= 0) {
        H5Gclose(group_id);
    }

    // Fuzz the H5Gopen1 function
    hid_t result = H5Gopen1(file_id, group_name);

    // Clean up
    if (result >= 0) {
        H5Gclose(result);
    }
    H5Fclose(file_id);
    free(group_name);
    H5close();

    return 0;
}