// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_array_merge at ucl_util.c:3193:6 in ucl.h
// ucl_object_merge at ucl_util.c:2551:6 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_copy at ucl_util.c:3692:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_elt_append at ucl_util.c:3397:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static ucl_object_t* create_random_ucl_object(const uint8_t *Data, size_t Size) {
    ucl_object_t *obj = ucl_object_new();
    if (Size > 0) {
        obj->value.sv = (const char *)Data;
        obj->len = Size;
    }
    return obj;
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create UCL objects
    ucl_object_t *obj1 = create_random_ucl_object(Data, Size);
    ucl_object_t *obj2 = create_random_ucl_object(Data, Size);

    // Create iterators
    ucl_object_iter_t iter = ucl_object_iterate_new(obj1);

    // Test ucl_object_iterate_safe
    const ucl_object_t *next_obj = ucl_object_iterate_safe(iter, Data[0] % 2);
    
    // Test ucl_array_merge
    bool merge_result = ucl_array_merge(obj1, obj2, Data[0] % 2);

    // Test ucl_object_merge
    bool object_merge_result = ucl_object_merge(obj1, obj2, Data[0] % 2);

    // Test ucl_array_delete
    ucl_object_t *deleted_obj = ucl_array_delete(obj1, obj2);
    if (deleted_obj != NULL) {
        ucl_object_unref(deleted_obj);
    }

    // Test ucl_object_copy
    ucl_object_t *copied_obj = ucl_object_copy(obj1);
    if (copied_obj != NULL) {
        ucl_object_unref(copied_obj);
    }

    // Test ucl_elt_append
    ucl_object_t *appended_obj = ucl_elt_append(NULL, obj2);
    if (appended_obj != NULL && appended_obj != obj2) {
        ucl_object_unref(appended_obj);
    }

    // Cleanup
    if (obj1 != NULL) {
        ucl_object_unref(obj1);
    }
    if (obj2 != NULL) {
        ucl_object_unref(obj2);
    }
    ucl_object_iterate_free(iter);

    return 0;
}