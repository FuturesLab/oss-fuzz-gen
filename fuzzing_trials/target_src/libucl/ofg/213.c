#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Ensure that the size is greater than 0 to proceed
    if (size == 0) {
        return 0;
    }

    // Create a ucl_object_t instance
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

    // Use the first byte of data to determine the reserve size
    size_t reserve_size = (size_t)data[0];

    // Call the function-under-test
    bool result = ucl_object_reserve(obj, reserve_size);

    // Clean up the ucl_object_t instance
    ucl_object_unref(obj);

    return 0;
}