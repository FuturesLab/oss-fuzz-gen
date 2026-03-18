#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    unsigned int intent;
    herr_t status;

    // Create an HDF5 file in memory
    file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Unable to create file, exit
    }

    // Call the function-under-test
    status = H5Fget_intent(file_id, &intent);

    // Close the file
    H5Fclose(file_id);

    return 0;
}