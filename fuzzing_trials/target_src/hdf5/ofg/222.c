#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t attr_id = H5I_INVALID_HID;
    H5A_info_t ainfo;

    // Ensure the size is sufficient for processing
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Use the input data to simulate a valid hid_t
    attr_id = (hid_t)(*(const hid_t *)data);

    // Call the function-under-test
    herr_t status = H5Aget_info(attr_id, &ainfo);

    // Optionally handle the status
    if (status < 0) {
        // Handle error if necessary
    }

    return 0;
}