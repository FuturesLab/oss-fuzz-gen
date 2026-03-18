// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_pop_first at ucl_util.c:3303:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    // Extract a double value from the input data
    double dv;
    memcpy(&dv, Data, sizeof(double));

    // Create a UCL object from the double
    ucl_object_t *obj = ucl_object_fromdouble(dv);
    if (obj == NULL) {
        return 0;
    }

    // Create an array object
    ucl_object_t *array = ucl_object_fromdouble(0); // Dummy initialization
    if (array == NULL) {
        ucl_object_unref(obj);
        return 0;
    }
    array->type = UCL_ARRAY; // Set type to array

    // Prepend the object to the array
    bool result = ucl_array_prepend(array, obj);
    if (!result) {
        ucl_object_unref(obj);
        ucl_object_unref(array);
        return 0;
    }

    // Pop the first element from the array
    ucl_object_t *popped_obj = ucl_array_pop_first(array);
    if (popped_obj != NULL) {
        // Unreference the popped object
        ucl_object_unref(popped_obj);
    }

    // Unreference the array object
    ucl_object_unref(array);

    return 0;
}