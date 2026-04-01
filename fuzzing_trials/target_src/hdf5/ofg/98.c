#include <stdint.h>
#include <stdlib.h>
#include <H5Apublic.h>
#include <H5public.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t value from the input data
    hid_t attribute_id = *(const hid_t *)data;

    // Call the function-under-test
    hsize_t storage_size = H5Aget_storage_size(attribute_id);

    // Use the result to prevent any compiler optimizations that might skip the function call
    if (storage_size == 0) {
        // Do something trivial
        return 0;
    }

    return 0;
}