#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id = -1; // Invalid file identifier
    hid_t fapl_id = -1; // Invalid file access property list identifier
    void *file_handle = NULL;

    // Check if the size is sufficient to create a valid file name
    if (size > 0) {
        // Create a temporary file name using the provided data
        char filename[256];
        snprintf(filename, sizeof(filename), "/tmp/hdf5_fuzz_%.*s", (int)size, data);

        // Create a file access property list
        fapl_id = H5Pcreate(H5P_FILE_ACCESS);
        if (fapl_id < 0) {
            return 0;
        }

        // Create a new file using the file access property list
        file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);
        if (file_id < 0) {
            H5Pclose(fapl_id);
            return 0;
        }

        // Call the function-under-test
        herr_t status = H5Fget_vfd_handle(file_id, fapl_id, &file_handle);

        // Clean up
        H5Fclose(file_id);
        H5Pclose(fapl_id);
    }

    return 0;
}