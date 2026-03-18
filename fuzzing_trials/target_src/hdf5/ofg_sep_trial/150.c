#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Ensure the size of data is at least the size of hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Interpret the first bytes of data as a hid_t
    hid_t file_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t plist_id = H5Fget_create_plist(file_id);

    // Close the property list if it is valid
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}