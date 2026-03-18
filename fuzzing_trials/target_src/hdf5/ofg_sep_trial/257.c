#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_257(const uint8_t *data, size_t size) {
    // Ensure data is large enough to create two strings
    if (size < 4) {
        return 0;
    }

    // Create a copy of the input data to manipulate
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Split the input data into two strings
    size_t mid_point = size / 2;
    char *name1 = input_data;
    char *name2 = input_data + mid_point;

    // Ensure both names are null-terminated
    name1[mid_point - 1] = '\0';
    name2[size - mid_point - 1] = '\0';

    // Initialize HDF5 library
    H5open();

    // Create a file and two groups for testing
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hid_t group1_id = H5Gcreate2(file_id, "group1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    hid_t group2_id = H5Gcreate2(file_id, "group2", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Call the function under test
    herr_t status = H5Gmove2(group1_id, name1, group2_id, name2);

    // Clean up
    H5Gclose(group1_id);
    H5Gclose(group2_id);
    H5Fclose(file_id);
    H5close();

    free(input_data);

    return 0;
}