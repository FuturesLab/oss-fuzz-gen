#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_265(const uint8_t *data, size_t size) {
    // Ensure size is large enough to extract an hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the input data
    hid_t input_id = *((hid_t *)data);

    // Call the function-under-test
    hid_t plist_id = H5Aget_create_plist(input_id);

    // Close the property list if it is valid
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif