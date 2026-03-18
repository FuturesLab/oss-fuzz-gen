#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Ensure there is enough data to interpret as an hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Interpret the first part of the data as an hid_t
    hid_t file_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t plist_id = H5Fget_create_plist(file_id);

    // Close the property list if it was successfully created
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}