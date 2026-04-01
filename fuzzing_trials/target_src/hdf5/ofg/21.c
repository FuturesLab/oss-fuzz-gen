#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = H5I_INVALID_HID; // Initialize with an invalid ID
    double hit_rate = 0.0;
    herr_t status;

    // Check if size is sufficient to create a valid file_id
    if (size >= sizeof(hid_t)) {
        // Use the data to create a valid file_id
        file_id = *((hid_t *)data);
    }

    // Call the function-under-test
    status = H5Fget_mdc_hit_rate(file_id, &hit_rate);

    // Ensure file_id is closed if it was opened
    if (file_id != H5I_INVALID_HID) {
        H5Fclose(file_id);
    }

    return 0;
}