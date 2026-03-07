#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an int64_t value
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Extract an int64_t value from the input data
    int64_t value = *(const int64_t *)data;

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_fromint(value);

    // Clean up the created ucl_object_t
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}