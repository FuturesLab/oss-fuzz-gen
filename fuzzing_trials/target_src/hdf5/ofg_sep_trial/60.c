#include <stdint.h>
#include <hdf5.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    hid_t dataset_id;
    hid_t access_plist_id;

    // Ensure that the size is sufficient to create a valid hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Use the input data to create a hid_t value
    dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    access_plist_id = H5Dget_access_plist(dataset_id);

    // Check if the access_plist_id is valid
    if (access_plist_id >= 0) {
        // Close the property list if it was successfully opened
        H5Pclose(access_plist_id);
    }

    return 0;
}