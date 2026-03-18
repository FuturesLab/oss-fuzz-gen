#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    hid_t file_id;
    herr_t status;
    
    // Ensure that the size of data is sufficient to create a valid file name
    if (size < 5) {
        return 0;
    }

    // Create a temporary HDF5 file to work with
    char filename[256];
    snprintf(filename, sizeof(filename), "/tmp/fuzzfile_%02x%02x%02x%02x.h5", data[0], data[1], data[2], data[3]);

    // Create a new file using default properties.
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit early
    }

    // Call the function-under-test
    status = H5Fstart_swmr_write(file_id);

    // Close the file
    H5Fclose(file_id);

    // Remove the temporary file
    remove(filename);

    return 0;
}