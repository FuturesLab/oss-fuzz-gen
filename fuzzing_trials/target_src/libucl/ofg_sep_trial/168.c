#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a double
    if (size < sizeof(double)) {
        return 0;
    }

    // Convert the first bytes of data to a double
    double value;
    // Copy bytes to avoid alignment issues
    memcpy(&value, data, sizeof(double));

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_fromdouble(value);

    // Free the created object to avoid memory leaks
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}