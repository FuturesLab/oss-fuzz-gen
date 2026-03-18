#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    hid_t file_id;
    char *name_buf;
    ssize_t name_len;
    size_t buf_size;

    // Initialize HDF5 library
    H5open();

    // Create a temporary file to get a valid file_id
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Ensure the file was created successfully
    if (file_id < 0) {
        return 0;
    }

    // Allocate a buffer for the name
    buf_size = 256; // Arbitrary buffer size for the file name
    name_buf = (char *)malloc(buf_size);
    if (name_buf == NULL) {
        H5Fclose(file_id);
        return 0;
    }

    // Call the function-under-test
    name_len = H5Fget_name(file_id, name_buf, buf_size);

    // Clean up
    free(name_buf);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}