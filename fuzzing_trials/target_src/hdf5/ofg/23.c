#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    double hit_rate = 0.0;
    herr_t status;

    // Ensure the input size is sufficient for creating a file name
    if (size < 1) {
        return 0;
    }

    // Create a unique file name using the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "fuzz_test_%u.h5", data[0]);

    // Create a new HDF5 file using the input data
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    status = H5Fget_mdc_hit_rate(file_id, &hit_rate);

    // Close the file
    H5Fclose(file_id);

    return 0;
}