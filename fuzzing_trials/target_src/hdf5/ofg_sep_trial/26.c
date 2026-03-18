#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    unsigned int intent;
    herr_t status;

    // Create a memory buffer for the file
    hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
    if (fapl_id < 0) {
        return 0;
    }

    // Create a unique file name using the input data to avoid conflicts
    char filename[256];
    snprintf(filename, sizeof(filename), "tempfile_%zu", size);

    hid_t mem_file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);
    
    // Check if the file was created successfully
    if (mem_file_id < 0) {
        H5Pclose(fapl_id);
        return 0;
    }

    // Use the file ID from the created file
    file_id = mem_file_id;

    // Call the function-under-test
    status = H5Fget_intent(file_id, &intent);

    // Close the file and property list
    H5Fclose(file_id);
    H5Pclose(fapl_id);

    return 0;
}