#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file in memory to get a valid hid_t
    hid_t file_id = H5Fcreate("tempfile", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Initialize H5F_info2_t structure
    H5F_info2_t file_info;
    
    // Call the function-under-test
    herr_t status = H5Fget_info2(file_id, &file_info);

    // Close the file and clean up
    H5Fclose(file_id);
    H5close();

    return 0;
}