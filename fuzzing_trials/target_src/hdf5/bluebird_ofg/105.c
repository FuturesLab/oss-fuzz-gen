#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Declare and initialize variables
    hid_t dataset_id = H5I_INVALID_HID;  // Invalid ID to start with
    hid_t file_space_id = H5I_INVALID_HID;  // Invalid ID to start with
    hsize_t num_chunks = 0;

    // Ensure the data size is sufficient to create valid IDs
    if (size >= sizeof(hid_t) * 2) {
        // Use the data to create IDs, casting to hid_t
        dataset_id = *((hid_t*)data);
        file_space_id = *((hid_t*)(data + sizeof(hid_t)));

        // Call the function-under-test
        herr_t status = H5Dget_num_chunks(dataset_id, file_space_id, &num_chunks);

        // Optionally, handle the status or num_chunks if needed
        (void)status;  // Suppress unused variable warning
    }

    // Close HDF5 library
    H5close();

    return 0;
}