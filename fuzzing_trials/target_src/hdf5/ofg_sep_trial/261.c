#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the input data
    hid_t input_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t plist_id = H5Aget_create_plist(input_id);

    // Normally, you would do something with plist_id, like checking its validity
    // For fuzzing, we just ensure the function is called
    if (plist_id >= 0) {
        // Close the property list if it was successfully retrieved
        H5Pclose(plist_id);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif