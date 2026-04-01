#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h> // Include this for the bool type

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure that size is at least 1 to read a byte for the boolean value
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the boolean value
    bool bool_value = data[0] % 2 == 0; // Even byte values as false, odd as true

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_frombool(bool_value);

    // Clean up the created object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}