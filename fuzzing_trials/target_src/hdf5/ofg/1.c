#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a copy of the data to ensure it is null-terminated
    char *group_name = (char *)malloc(size + 1);
    if (group_name == NULL) {
        return 0;
    }
    memcpy(group_name, data, size);
    group_name[size] = '\0';

    // Initialize a valid HDF5 file and obtain a file identifier
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        free(group_name);
        return 0;
    }

    // Create a group in the file to ensure H5Gopen1 has something to open
    hid_t group_id = H5Gcreate1(file_id, "testgroup", 0);
    if (group_id >= 0) {
        H5Gclose(group_id);
    }

    // Call the function-under-test
    hid_t result = H5Gopen1(file_id, group_name);

    // Cleanup
    if (result >= 0) {
        H5Gclose(result);
    }
    H5Fclose(file_id);
    free(group_name);

    return 0;
}