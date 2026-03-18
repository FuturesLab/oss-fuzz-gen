#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for an hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t from the input data
    hid_t input_hid = *((hid_t *)data);

    // Call the function-under-test
    hid_t plist_id = H5Aget_create_plist(input_hid);

    // Normally, you would do something with plist_id, like checking its validity
    // For fuzzing purposes, we can simply close it if it's valid
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}