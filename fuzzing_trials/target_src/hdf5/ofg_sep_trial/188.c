#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to split into two non-empty strings
    if (size < 2) return 0;

    // Initialize HDF5 library
    H5open();

    // Create a new file using the default properties.
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create a group in the file.
    hid_t group_id = H5Gcreate2(file_id, "/fuzz_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Split the input data into two parts for name and comment
    size_t mid = size / 2;
    char *name = (char *)malloc(mid + 1);
    char *comment = (char *)malloc(size - mid + 1);

    memcpy(name, data, mid);
    name[mid] = '\0';

    memcpy(comment, data + mid, size - mid);
    comment[size - mid] = '\0';

    // Call the function-under-test
    herr_t status = H5Gset_comment(group_id, name, comment);

    // Clean up
    free(name);
    free(comment);
    H5Gclose(group_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}