#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    hid_t file_id;
    void *buffer;
    ssize_t result;

    // Initialize HDF5 library
    H5open();

    // Create a new HDF5 file to get a valid hid_t
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Allocate buffer of the same size as input data
    buffer = malloc(size);
    if (buffer == NULL) {
        H5Fclose(file_id);
        return 0;
    }

    // Call the function-under-test
    result = H5Fget_file_image(file_id, buffer, size);

    // Clean up
    free(buffer);
    H5Fclose(file_id);
    H5close();

    return 0;
}