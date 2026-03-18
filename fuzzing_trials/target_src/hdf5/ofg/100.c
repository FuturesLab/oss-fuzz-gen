#include <stdint.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    hid_t file_id;
    herr_t status;

    // Ensure we have enough data to create a valid file name
    if (size < 1) {
        return 0;
    }

    // Create a simple file name based on the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "fuzz_test_%u.h5", data[0]);

    // Create a new HDF5 file using default properties
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function under test
    status = H5Fstart_mdc_logging(file_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}