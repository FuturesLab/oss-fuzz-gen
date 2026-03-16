#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    H5F_info2_t file_info;

    // Create a temporary in-memory file
    file_id = H5Fcreate("tempfile", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // If file creation fails, exit the fuzzer
    }

    // Call the function-under-test
    herr_t status = H5Fget_info2(file_id, &file_info);

    // Close the file
    H5Fclose(file_id);

    return 0;
}