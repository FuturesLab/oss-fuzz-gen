#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    hid_t file_id;
    hssize_t free_space;

    // Creating a temporary file to get a valid hid_t
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file
    }

    // Call the function-under-test
    free_space = H5Fget_freespace(file_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}