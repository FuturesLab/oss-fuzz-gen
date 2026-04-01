#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t dataset_id = *((const hid_t *)data);

    // Call the function-under-test
    hid_t plist_id = H5Dget_create_plist(dataset_id);

    // Perform cleanup if necessary
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}