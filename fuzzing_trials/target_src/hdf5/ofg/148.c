#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure that size is large enough to extract a valid hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t value from the input data
    hid_t file_id = *((const hid_t *)data);

    // Call the function-under-test
    hid_t plist_id = H5Fget_create_plist(file_id);

    // Perform any necessary cleanup
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}