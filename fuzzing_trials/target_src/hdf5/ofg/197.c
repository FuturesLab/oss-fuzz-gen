#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    hid_t file_id;
    unsigned long fileno;
    herr_t status;

    // Ensure the data size is sufficient for a valid filename
    if (size < 5) {
        return 0;
    }

    // Create a temporary file using the input data as part of the filename
    char filename[256];
    snprintf(filename, sizeof(filename), "/tmp/fuzzfile_%.*s.h5", (int)(size - 1), data);

    // Create an HDF5 file to obtain a valid hid_t
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    status = H5Fget_fileno(file_id, &fileno);

    // Close the HDF5 file
    H5Fclose(file_id);

    return 0;
}