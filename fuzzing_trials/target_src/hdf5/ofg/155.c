#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Declare and initialize the variable for the function-under-test
    hid_t file_id = -1; // Initialize with an invalid file identifier

    // Ensure we have enough data to proceed
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract hid_t from the input data
    file_id = *((hid_t *)data);

    // Call the function-under-test
    hid_t access_plist_id = H5Fget_access_plist(file_id);

    // Clean up if a valid access property list was returned
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    return 0;
}