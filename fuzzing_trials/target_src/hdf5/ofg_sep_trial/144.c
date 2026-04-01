#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    hid_t file_id;
    hssize_t free_space;

    // Initialize the HDF5 library
    H5open();

    // Create a unique file name using the data
    char filename[256];
    snprintf(filename, sizeof(filename), "/tmp/fuzz_hdf5_%zu.h5", size);

    // Create a new HDF5 file using the filename
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        // Failed to create the file, return
        return 0;
    }

    // Call the function-under-test
    free_space = H5Fget_freespace(file_id);

    // Close the file
    H5Fclose(file_id);

    // Clean up the HDF5 library
    H5close();

    return 0;
}