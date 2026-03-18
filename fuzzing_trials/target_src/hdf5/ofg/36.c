#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a temporary file to work with
    hid_t file_id = H5Fcreate("temp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a group in the file
    hid_t group_id = H5Gcreate(file_id, "/test_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Close the group
    H5Gclose(group_id);

    // Prepare a null-terminated string from the input data
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        H5Fclose(file_id);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    herr_t status = H5Gunlink(file_id, name);

    // Clean up
    free(name);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}