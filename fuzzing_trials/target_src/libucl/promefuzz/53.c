// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_merge at ucl_util.c:3193:6 in ucl.h
// ucl_elt_append at ucl_util.c:3397:1 in ucl.h
// ucl_array_head at ucl_util.c:3258:1 in ucl.h
// ucl_array_tail at ucl_util.c:3271:1 in ucl.h
// ucl_array_pop_last at ucl_util.c:3283:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
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

static ucl_object_t* create_random_ucl_array(const uint8_t *Data, size_t Size) {
    // Create a simple UCL array object for testing
    ucl_object_t *array = ucl_object_new();
    if (array) {
        array->type = UCL_ARRAY;
        array->value.av = NULL;
    }
    return array;
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    // Create two UCL arrays for testing
    ucl_object_t *array1 = create_random_ucl_array(Data, Size);
    ucl_object_t *array2 = create_random_ucl_array(Data, Size);

    if (!array1 || !array2) {
        if (array1) ucl_object_unref(array1);
        if (array2) ucl_object_unref(array2);
        return 0;
    }

    // Test ucl_array_merge
    bool copy = (Size > 0) ? (Data[0] % 2 == 0) : false;
    bool result = ucl_array_merge(array1, array2, copy);

    // Test ucl_elt_append
    ucl_object_t *new_head = ucl_elt_append(array1, array2);

    // Test ucl_array_head
    const ucl_object_t *head = ucl_array_head(array1);

    // Test ucl_array_tail
    const ucl_object_t *tail = ucl_array_tail(array1);

    // Test ucl_array_pop_last
    ucl_object_t *popped = ucl_array_pop_last(array1);
    if (popped) {
        ucl_object_unref(popped);
    }

    // Test ucl_array_delete
    ucl_object_t *deleted = ucl_array_delete(array1, array2);
    if (deleted) {
        ucl_object_unref(deleted);
    }

    // Cleanup
    // Ensure array2 is not used after being freed
    if (!result) {
        ucl_object_unref(array2);
    }
    ucl_object_unref(array1);

    return 0;
}