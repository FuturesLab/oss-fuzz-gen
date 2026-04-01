#include <stdint.h>
#include <hdf5.h>
#include <stdio.h> // Include stdio.h for snprintf

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    hid_t file_id;
    herr_t status;

    // Ensure the size is sufficient for a file name
    if (size < 1) {
        return 0;
    }

    // Create a temporary file name using the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "fuzz_test_%.*s.h5", (int)size, data);

    // Create a new HDF5 file using the input data as part of the filename
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    status = H5Fformat_convert(file_id);

    // Close the file
    H5Fclose(file_id);

    return 0;
}