#include <stdint.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    hid_t file_id;

    // Ensure we have enough data to create a file name
    if (size < 1) {
        return 0;
    }

    // Create a unique file name using the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "fuzz_test_%02x.h5", data[0]);

    // Create a new HDF5 file using default properties
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit
    }

    // Call the function-under-test
    H5Freset_mdc_hit_rate_stats(file_id);

    // Close the file
    H5Fclose(file_id);

    // Optionally, remove the file after the test
    remove(filename);

    return 0;
}