#include <stdint.h>
#include <hdf5.h>
#include <stdlib.h>
#include <stdio.h> // Include stdio.h for snprintf

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id = -1;
    haddr_t address = 0;

    // Ensure that the size is sufficient to create a file name
    if (size < 5) {
        return 0;
    }

    // Create a temporary file name from the input data
    char filename[6];
    snprintf(filename, sizeof(filename), "fuzz_%c%c%c%c", data[0], data[1], data[2], data[3]);

    // Create a new HDF5 file using the input data
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    H5Fget_eoa(file_id, &address);

    // Close the file
    H5Fclose(file_id);

    return 0;
}