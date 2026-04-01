#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure that the size of the data is sufficient to extract an hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the input data
    hid_t dataset_id = *((const hid_t *)data);

    // Call the function-under-test
    hid_t plist_id = H5Dget_create_plist(dataset_id);

    // Close the property list if it is valid
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}