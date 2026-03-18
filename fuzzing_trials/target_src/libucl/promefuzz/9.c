// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
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
#include <stdio.h>
#include <stdbool.h>
#include <ucl.h>

static ucl_object_t* create_random_ucl_object(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return NULL;

    ucl_object_t *obj = ucl_object_typed_new(UCL_FLOAT);
    if (!obj) return NULL;

    obj->value.dv = *(double *)Data;
    return obj;
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 2) return 0; // Ensure enough data for two doubles

    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *element = create_random_ucl_object(Data, Size);
    ucl_object_t *element_to_delete = create_random_ucl_object(Data + sizeof(double), Size - sizeof(double));

    if (!array || !element || !element_to_delete) {
        if (array) ucl_object_unref(array);
        if (element) ucl_object_unref(element);
        if (element_to_delete) ucl_object_unref(element_to_delete);
        return 0;
    }

    // Test ucl_array_append
    bool append_result = ucl_array_append(array, element);

    // Test ucl_array_delete
    ucl_object_t *deleted_element = ucl_array_delete(array, element_to_delete);

    // Test ucl_object_todouble
    double value = ucl_object_todouble(element);

    // Cleanup
    if (deleted_element) {
        ucl_object_unref(deleted_element);
    }
    ucl_object_unref(array);
    ucl_object_unref(element_to_delete);

    return 0;
}