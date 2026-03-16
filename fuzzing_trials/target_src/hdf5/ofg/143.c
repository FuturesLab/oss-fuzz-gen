#include <stdint.h>
#include <stdio.h>
#include <hdf5.h>

// Initialize HDF5 library
static hid_t initialize_hdf5() {
    hid_t file_id;
    // Create a new HDF5 file using default properties.
    file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    return file_id;
}

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    hid_t file_id;
    hssize_t free_space;

    // Initialize HDF5 file
    file_id = initialize_hdf5();
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    free_space = H5Fget_freespace(file_id);

    // Print the free space (for debugging purposes)
    printf("Free space: %lld\n", (long long)free_space);

    // Close the HDF5 file
    H5Fclose(file_id);

    return 0;
}