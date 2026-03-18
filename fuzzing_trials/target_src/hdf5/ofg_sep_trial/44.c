#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the input data
    hid_t dataset_id;
    memcpy(&dataset_id, data, sizeof(hid_t));

    // Call the function-under-test
    hid_t plist_id = H5Dget_create_plist(dataset_id);

    // If plist_id is valid, close it to prevent resource leaks
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}