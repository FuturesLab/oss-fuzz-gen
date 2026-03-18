#include <stdint.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Declare and initialize the hid_t variable
    hid_t file_id;

    // Check if the size is sufficient for creating a file name
    if (size < 1) {
        return 0;
    }

    // Create a temporary file name using the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "/tmp/fuzz_file_%d.h5", data[0]);

    // Create a new HDF5 file using the filename
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    herr_t result = H5Fclear_elink_file_cache(file_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}