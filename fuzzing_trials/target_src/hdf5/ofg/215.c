#include <stdint.h>
#include <hdf5.h>
#include <stdio.h>  // Include this for snprintf

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    hid_t file_id = H5I_INVALID_HID;

    // Check if the data size is sufficient to create a valid file name
    if (size > 0 && size < 255) {
        // Create a temporary file name from the input data
        char filename[256];
        snprintf(filename, sizeof(filename), "/tmp/fuzz_hdf5_%.*s.h5", (int)size, data);

        // Create a new HDF5 file using the filename
        file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        if (file_id >= 0) {
            // Call the function-under-test
            H5Fclear_elink_file_cache(file_id);

            // Close the file
            H5Fclose(file_id);
        }
    }

    return 0;
}