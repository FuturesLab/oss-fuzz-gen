// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ucl.h"

static ucl_object_t* create_ucl_object(double value) {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj != NULL) {
        memset(obj, 0, sizeof(ucl_object_t)); // Initialize all fields to zero
        obj->value.dv = value;
        obj->ref = 1;
        obj->type = UCL_FLOAT; // Assuming type is UCL_FLOAT for simplicity
    }
    return obj;
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    double value;
    memcpy(&value, Data, sizeof(double));

    ucl_object_t *array = ucl_object_new(); // Create a new UCL object as an array
    ucl_object_t *element = create_ucl_object(value);

    if (array == NULL || element == NULL) {
        ucl_object_unref(array);
        free(element);
        return 0;
    }

    // Test ucl_array_append
    bool append_result = ucl_array_append(array, element);

    // Test ucl_array_delete
    ucl_object_t *deleted_element = ucl_array_delete(array, element);

    // Test ucl_object_todouble
    if (deleted_element != NULL) {
        double converted_value = ucl_object_todouble(deleted_element);
        ucl_object_unref(deleted_element);
    } else {
        ucl_object_unref(element);
    }

    // Cleanup
    ucl_object_unref(array);

    return 0;
}