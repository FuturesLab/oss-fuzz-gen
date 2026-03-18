#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for an `hid_t` value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Interpret the first bytes of data as an `hid_t` value
    hid_t dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t plist_id = H5Dget_create_plist(dataset_id);

    // If a valid property list ID is returned, close it to prevent resource leaks
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}