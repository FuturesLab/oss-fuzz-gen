#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract necessary parameters
    if (size < sizeof(hid_t) * 2) {
        return 0;
    }

    // Extract parameters from the input data
    hid_t file_id = *(const hid_t *)data;
    hid_t estack_id = *(const hid_t *)(data + sizeof(hid_t));

    // Call the function-under-test
    herr_t result = H5Fclose_async(file_id, estack_id);

    (void)result; // Suppress unused variable warning

    return 0;
}

#ifdef __cplusplus
}
#endif