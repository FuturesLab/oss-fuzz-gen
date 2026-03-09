// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_fromdouble at ucl_util.c:3104:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_pop_last at ucl_util.c:3283:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    double dv;
    memcpy(&dv, Data, sizeof(double));

    // Step 1: Create a UCL object from double
    ucl_object_t *obj_from_double = ucl_object_fromdouble(dv);
    if (obj_from_double == NULL) {
        return 0;
    }

    // Step 2: Create an array object
    ucl_object_t *array_obj = ucl_object_fromdouble(0.0); // Initialize as a valid UCL array
    if (array_obj == NULL) {
        ucl_object_unref(obj_from_double);
        return 0;
    }
    array_obj->type = UCL_ARRAY; // Explicitly set type to array

    // Step 3: Append the double object to the array
    bool append_result = ucl_array_append(array_obj, obj_from_double);
    if (!append_result) {
        ucl_object_unref(obj_from_double);
        ucl_object_unref(array_obj);
        return 0;
    }

    // Step 4: Pop the last element from the array
    ucl_object_t *popped_obj = ucl_array_pop_last(array_obj);
    if (popped_obj != NULL) {
        // Step 5: Convert the popped object back to double
        double result = ucl_object_todouble(popped_obj);
        (void)result; // Use the result to avoid unused variable warning

        // Cleanup
        ucl_object_unref(popped_obj);
    }

    // Cleanup remaining objects
    ucl_object_unref(array_obj);

    return 0;
}