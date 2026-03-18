#include <stdint.h>
#include <stdbool.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = H5I_INVALID_HID;  // Invalid ID to start with
    bool no_attrs_hint = false;

    // Check if size is sufficient to extract values
    if (size < sizeof(hid_t) + sizeof(bool)) {
        return 0;
    }

    // Extract values from data
    file_id = *(hid_t *)data;
    no_attrs_hint = *(bool *)(data + sizeof(hid_t));

    // Call the function-under-test
    herr_t result = H5Fset_dset_no_attrs_hint(file_id, no_attrs_hint);

    // Return 0 to indicate successful execution
    return 0;
}