#include <stdint.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    hid_t file_id;

    // Ensure that the data size is sufficient to create a unique file name
    if (size < 1) {
        return 0;
    }

    // Create a unique file name using the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "fuzz_test_%d.h5", data[0]);

    // Create a new HDF5 file using the unique file name
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Start metadata cache logging
    if (H5Fstart_mdc_logging(file_id) < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Call the function-under-test
    H5Fstop_mdc_logging(file_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}