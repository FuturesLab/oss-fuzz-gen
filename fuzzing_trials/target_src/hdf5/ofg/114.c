#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    hid_t file_id;
    herr_t status;

    // Ensure the data size is sufficient to create a valid file name
    if (size < 1) {
        return 0;
    }

    // Create a unique file name using the input data
    char filename[256];
    snprintf(filename, sizeof(filename), "fuzz_test_%u.h5", data[0]);

    // Create a new file using the HDF5 library
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Check if the file was created successfully
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    status = H5Fstart_swmr_write(file_id);

    // Close the file
    H5Fclose(file_id);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}