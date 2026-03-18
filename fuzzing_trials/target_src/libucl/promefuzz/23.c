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

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0; // Not enough data to read a double
    }

    // Extract a double from the input data
    double dv;
    memcpy(&dv, Data, sizeof(double));

    // Create a UCL object from the double
    ucl_object_t *obj = ucl_object_fromdouble(dv);
    if (obj == NULL) {
        return 0; // Failed to create object
    }

    // Create an array object
    ucl_object_t *array = ucl_object_fromdouble(0.0); // Initialize as a float
    if (array == NULL) {
        ucl_object_unref(obj);
        return 0; // Failed to create array
    }

    // Append the object to the array
    bool append_result = ucl_array_append(array, obj);
    if (!append_result) {
        ucl_object_unref(obj);
        ucl_object_unref(array);
        return 0; // Failed to append to array
    }

    // Pop the last element from the array
    ucl_object_t *popped = ucl_array_pop_last(array);
    if (popped != NULL) {
        // Convert the popped object to a double
        double result = ucl_object_todouble(popped);
        (void)result; // Use result to avoid unused variable warning
        ucl_object_unref(popped);
    }

    // Cleanup
    ucl_object_unref(array);

    return 0;
}