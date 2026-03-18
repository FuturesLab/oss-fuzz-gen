#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract all necessary parameters
    if (size < 20) {
        return 0;
    }

    // Extract parameters from the input data
    hid_t attr_id = *(hid_t *)(data);
    hid_t type_id = *(hid_t *)(data + 4);
    const void *buf = (const void *)(data + 8);
    hid_t es_id = *(hid_t *)(data + 12);

    // Call the function-under-test
    herr_t result = H5Awrite_async(attr_id, type_id, buf, es_id);

    // Return 0 to indicate successful execution
    return 0;
}