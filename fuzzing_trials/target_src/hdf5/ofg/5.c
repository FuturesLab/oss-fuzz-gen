#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract at least two strings
    if (size < 2) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a file to operate on
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create two groups to move
    hid_t group1_id = H5Gcreate2(file_id, "/group1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    hid_t group2_id = H5Gcreate2(file_id, "/group2", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group1_id < 0 || group2_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Close the groups
    H5Gclose(group1_id);
    H5Gclose(group2_id);

    // Extract two string lengths from the data
    size_t len1 = data[0] % size;
    size_t len2 = (data[1] % (size - len1)) % size;

    // Ensure the lengths are within bounds and there is enough data
    if (len1 + len2 + 2 > size) {
        H5Fclose(file_id);
        return 0;
    }

    // Extract the strings from the data
    char *src_name = (char *)malloc(len1 + 1);
    char *dst_name = (char *)malloc(len2 + 1);
    if (src_name == NULL || dst_name == NULL) {
        free(src_name);
        free(dst_name);
        H5Fclose(file_id);
        return 0;
    }

    memcpy(src_name, &data[2], len1);
    src_name[len1] = '\0';
    memcpy(dst_name, &data[2 + len1], len2);
    dst_name[len2] = '\0';

    // Call the function under test
    H5Gmove(file_id, src_name, dst_name);

    // Clean up
    free(src_name);
    free(dst_name);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}