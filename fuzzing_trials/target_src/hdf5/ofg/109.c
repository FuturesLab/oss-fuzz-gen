#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Initialize a file identifier
    hid_t file_id;
    herr_t status;

    // Create a temporary file name using the provided data
    char filename[256];
    size_t filename_size = size < 255 ? size : 255;
    for (size_t i = 0; i < filename_size; ++i) {
        filename[i] = data[i] % 26 + 'A'; // Ensure filename is valid
    }
    filename[filename_size] = '\0';

    // Create a new HDF5 file using the filename
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // If file creation fails, exit early
    }

    // Call the function-under-test
    status = H5Fclose(file_id);

    // Return 0 indicating the fuzzer can continue
    return 0;
}