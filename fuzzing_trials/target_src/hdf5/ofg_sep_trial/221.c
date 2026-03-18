#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    hid_t file_id;
    hsize_t filesize;
    herr_t status;

    // Initialize the HDF5 library
    H5open();

    // Create a new HDF5 file using the data as the filename
    // Ensure the filename is null-terminated and not empty
    char filename[256];
    if (size > 255) size = 255;
    for (size_t i = 0; i < size; ++i) {
        filename[i] = (char)data[i];
    }
    filename[size] = '\0';

    // Create a new file using default properties.
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        // Failed to create file, exit the fuzzer
        return 0;
    }

    // Call the function-under-test
    status = H5Fget_filesize(file_id, &filesize);

    // Close the file
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}

#ifdef __cplusplus
}
#endif