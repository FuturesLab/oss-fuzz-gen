#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract required parameters
    if (size < 3) {
        return 0;
    }

    // Extract parameters from `data`
    hid_t obj_id = (hid_t)data[0];
    const char *attr_name = "test_attribute";  // Placeholder string, should be non-NULL
    _Bool exists;
    hid_t es_id = (hid_t)data[1];

    // Call the function-under-test
    herr_t result = H5Aexists_async(obj_id, attr_name, &exists, es_id);

    // Use the result in some way to avoid compiler optimizations
    if (result < 0) {
        // Handle error case
    }

    return 0;
}