#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t dataset_id = H5I_INVALID_HID;  // Invalid ID for testing
    hid_t file_space_id = H5I_INVALID_HID;  // Invalid ID for testing
    hsize_t nchunks = 0;

    // Call the function-under-test
    herr_t result = H5Dget_num_chunks(dataset_id, file_space_id, &nchunks);

    // Handle the result if needed (e.g., check for errors)
    if (result < 0) {
        // Handle error if necessary
    }

    return 0;
}