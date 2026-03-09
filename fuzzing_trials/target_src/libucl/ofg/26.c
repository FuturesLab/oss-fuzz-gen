#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the boolean value
    bool bool_value = (data[0] % 2 == 0); // Even numbers for true, odd for false

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_frombool(bool_value);

    // Clean up the created object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}