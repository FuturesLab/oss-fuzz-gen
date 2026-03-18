#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a group to move
    hid_t group_id = H5Gcreate(file_id, "/group1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Ensure the input data is large enough to be used as strings
    if (size < 2) {
        H5Gclose(group_id);
        H5Fclose(file_id);
        return 0;
    }

    // Use the input data to create source and destination strings
    size_t half_size = size / 2;
    char *source_name = (char *)malloc(half_size + 1);
    char *dest_name = (char *)malloc(size - half_size + 1);

    if (source_name == NULL || dest_name == NULL) {
        free(source_name);
        free(dest_name);
        H5Gclose(group_id);
        H5Fclose(file_id);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(source_name, data, half_size);
    source_name[half_size] = '\0';
    memcpy(dest_name, data + half_size, size - half_size);
    dest_name[size - half_size] = '\0';

    // Call the function under test
    herr_t status = H5Gmove(file_id, source_name, dest_name);

    // Clean up
    free(source_name);
    free(dest_name);
    H5Gclose(group_id);
    H5Fclose(file_id);

    return 0;
}