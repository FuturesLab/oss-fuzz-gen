#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Initialize a hid_t variable for testing
    hid_t file_id = H5Fopen("dummy_file.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    
    // Ensure the file_id is valid
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    herr_t result = H5Freset_page_buffering_stats(file_id);

    // Close the file to clean up
    H5Fclose(file_id);

    return 0;
}