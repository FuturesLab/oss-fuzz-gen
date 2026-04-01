#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    hid_t file_id;
    char *name;
    ssize_t name_len;
    size_t buffer_size;

    // Create a temporary file for testing
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Ensure size is not zero to avoid zero-length allocations
    buffer_size = size > 0 ? size : 1;

    // Allocate memory for the name buffer
    name = (char *)malloc(buffer_size);
    if (name == NULL) {
        H5Fclose(file_id);
        return 0;
    }

    // Copy data to the name buffer to simulate input
    memcpy(name, data, buffer_size - 1);
    name[buffer_size - 1] = '\0'; // Null-terminate the string

    // Call the function under test
    name_len = H5Fget_name(file_id, name, buffer_size);

    // Clean up
    free(name);
    H5Fclose(file_id);
    remove("tempfile.h5");

    return 0;
}