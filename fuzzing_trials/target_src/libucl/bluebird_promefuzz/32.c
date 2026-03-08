#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    // Convert the input data to a double
    double dv;
    memcpy(&dv, Data, sizeof(double));

    // Create a UCL object from the double
    ucl_object_t *obj = ucl_object_fromdouble(dv);
    if (obj == NULL) {
        return 0;
    }

    // Create an array object
    ucl_object_t *array = ucl_object_fromdouble(0.0); // Dummy initialization
    array->type = UCL_ARRAY;

    // Prepend the object to the array
    bool success = ucl_array_prepend(array, obj);

    // Pop the first element from the array
    ucl_object_t *popped = ucl_array_pop_first(array);
    if (popped != NULL) {
        ucl_object_unref(popped);
    }

    // Unreference the array object
    ucl_object_unref(array);

    return 0;
}