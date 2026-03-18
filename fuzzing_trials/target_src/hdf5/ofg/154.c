#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Initialize a hid_t variable
    hid_t file_id;

    // Check if size is large enough to extract a hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Copy bytes from data to file_id
    file_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t access_plist_id = H5Fget_access_plist(file_id);

    // Close the property list if it was successfully created
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    return 0;
}