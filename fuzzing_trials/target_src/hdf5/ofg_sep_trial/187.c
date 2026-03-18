#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract at least one character for each string
    if (size < 3) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a temporary file to work with
    hid_t file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a group in the file
    hid_t group_id = H5Gcreate2(file_id, "/test_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Extract strings from the input data
    size_t str1_len = (size - 1) / 2;
    size_t str2_len = size - 1 - str1_len;

    char *name = (char *)malloc(str1_len + 1);
    char *comment = (char *)malloc(str2_len + 1);

    if (name == NULL || comment == NULL) {
        H5Gclose(group_id);
        H5Fclose(file_id);
        free(name);
        free(comment);
        return 0;
    }

    memcpy(name, data, str1_len);
    name[str1_len] = '\0';

    memcpy(comment, data + str1_len, str2_len);
    comment[str2_len] = '\0';

    // Call the function-under-test
    H5Gset_comment(group_id, name, comment);

    // Clean up
    free(name);
    free(comment);
    H5Gclose(group_id);
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}