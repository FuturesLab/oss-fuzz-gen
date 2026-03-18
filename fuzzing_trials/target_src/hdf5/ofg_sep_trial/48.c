#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    hid_t file_id;
    char *name = NULL;
    char *comment = NULL;
    size_t comment_size = 256; // Arbitrary non-zero size for the comment buffer
    int result;

    // Ensure the input is large enough to be used
    if (size < 1) return 0;

    // Initialize HDF5 library
    H5open();

    // Create a temporary file to use as the HDF5 file
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) goto cleanup;

    // Allocate memory for name and comment
    name = (char*)malloc(size + 1);
    comment = (char*)malloc(comment_size);
    if (name == NULL || comment == NULL) goto cleanup;

    // Copy data into name and ensure it's null-terminated
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    result = H5Gget_comment(file_id, name, comment_size, comment);

    // Normally, you would check the result and handle errors here

cleanup:
    // Free allocated resources
    if (name != NULL) free(name);
    if (comment != NULL) free(comment);

    // Close the HDF5 file
    if (file_id >= 0) H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}