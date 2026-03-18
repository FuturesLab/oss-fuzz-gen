#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    hid_t attribute_id;
    hid_t plist_id;

    // Ensure we have enough data to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t from the input data
    attribute_id = *((hid_t *)data);

    // Call the function under test
    plist_id = H5Aget_create_plist(attribute_id);

    // Close the plist_id if it's valid
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}