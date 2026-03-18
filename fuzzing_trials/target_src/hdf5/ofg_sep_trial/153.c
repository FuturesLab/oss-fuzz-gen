#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Initialize parameters
    hid_t attr_id = H5I_INVALID_HID; // Invalid ID for fuzzing
    hid_t mem_type_id = H5T_NATIVE_INT; // Use native int type for simplicity
    hid_t es_id = H5I_INVALID_HID; // Invalid ID for fuzzing

    // Ensure data is not NULL and has some content
    if (size < sizeof(int)) {
        return 0;
    }

    // Use the data as the buffer to write
    const void *buf = (const void *)data;

    // Call the function-under-test
    herr_t result = H5Awrite_async(attr_id, mem_type_id, buf, es_id);

    // Return 0 to indicate the fuzzer can continue
    return 0;
}

#ifdef __cplusplus
}
#endif