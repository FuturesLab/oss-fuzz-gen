#include <stdint.h>
#include <hdf5.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    herr_t status;
    _Bool no_attrs_hint;

    // Check if the input size is sufficient
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract hid_t from input data
    file_id = *(const hid_t *)data;

    // Call the function-under-test
    status = H5Fget_dset_no_attrs_hint(file_id, &no_attrs_hint);

    // Use the result to prevent compiler optimizations
    if (status < 0) {
        // Handle error case if necessary
    }

    return 0;
}