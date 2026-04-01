#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include string.h for memcpy

int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    double value;
    memcpy(&value, data, sizeof(double));

    ucl_object_t *obj = ucl_object_fromdouble(value);

    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}