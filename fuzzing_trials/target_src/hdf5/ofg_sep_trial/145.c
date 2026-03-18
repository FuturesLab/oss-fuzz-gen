#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id = H5I_INVALID_HID;
    hid_t fapl_id = H5P_DEFAULT;
    void *vfd_handle = NULL;
    herr_t status;

    // Create a temporary file name
    char file_name[] = "tempfile.h5";

    // Create a new file using the default properties.
    file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;  // Return if file creation fails
    }

    // Call the function-under-test
    status = H5Fget_vfd_handle(file_id, fapl_id, &vfd_handle);

    // Close the file
    H5Fclose(file_id);

    // Return 0 indicating the fuzzer can continue
    return 0;
}