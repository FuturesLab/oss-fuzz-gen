#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    hid_t file_id;
    unsigned long fileno;
    herr_t status;

    // Ensure that the data size is sufficient for creating a file name
    if (size < 5) {
        return 0;
    }

    // Create a temporary file name from the input data
    char filename[6];
    snprintf(filename, sizeof(filename), "%.*s", 5, data);

    // Create a new HDF5 file using the input data as part of the file name
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    status = H5Fget_fileno(file_id, &fileno);

    // Close the file
    H5Fclose(file_id);

    return 0;
}