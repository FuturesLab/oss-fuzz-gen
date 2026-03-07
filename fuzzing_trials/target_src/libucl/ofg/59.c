#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0;
    }

    int64_t input_value;
    // Copy the first 8 bytes of data to input_value to ensure it is properly initialized
    memcpy(&input_value, data, sizeof(int64_t));

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_fromint(input_value);

    // Clean up the created object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}