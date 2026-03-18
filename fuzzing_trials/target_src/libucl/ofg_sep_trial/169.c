#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this for memcpy

int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    double input_double;
    memcpy(&input_double, data, sizeof(double));

    ucl_object_t *obj = ucl_object_fromdouble(input_double);

    // Free the created ucl object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}