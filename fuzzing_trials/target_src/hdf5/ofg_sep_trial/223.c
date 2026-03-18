#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for fuzzing
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Initialize variables
    hid_t attr_id;
    H5A_info_t ainfo;

    // Extract hid_t from the input data
    attr_id = *(const hid_t *)data;

    // Call the function under test
    herr_t status = H5Aget_info(attr_id, &ainfo);

    // Use the status and ainfo in some way to avoid unused variable warnings
    if (status >= 0) {
        // Optionally, perform some operations with ainfo
    }

    return 0;
}