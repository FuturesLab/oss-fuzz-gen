#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file identifier using H5Fcreate for fuzzing
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit early
    }

    // Prepare the intent variable
    unsigned int intent = 0;

    // Call the function-under-test
    herr_t result = H5Fget_intent(file_id, &intent);

    // Clean up by closing the file
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}