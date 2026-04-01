#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0;
    }

    int64_t input_value;
    // Copy the first 8 bytes from data into input_value
    // Ensure that the data is interpreted as an int64_t
    input_value = *(const int64_t *)data;

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_fromint(input_value);

    // Clean up the created object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}