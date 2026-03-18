#include <stdint.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    hid_t file_id;
    herr_t status;

    // Ensure that the input data is large enough to be used as a file name
    if (size < 5) {
        return 0;
    }

    // Create a file name from the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "fuzz_test_%.*s.h5", (int)size, data);

    // Create a new HDF5 file using the input data as part of the file name
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function under test
    status = H5Fformat_convert(file_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}