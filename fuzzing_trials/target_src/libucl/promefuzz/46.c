// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_array_merge at ucl_util.c:3193:6 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_pop_first at ucl_util.c:3303:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_pop_last at ucl_util.c:3283:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_elt_append at ucl_util.c:3397:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

static ucl_object_t* create_random_ucl_array() {
    ucl_object_t *arr = ucl_object_new();
    arr->type = UCL_ARRAY;
    return arr;
}

static ucl_object_t* create_random_ucl_object() {
    ucl_object_t *obj = ucl_object_new();
    obj->type = rand() % 2 == 0 ? UCL_ARRAY : UCL_OBJECT;
    return obj;
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *top = create_random_ucl_array();
    ucl_object_t *elt = create_random_ucl_array();
    ucl_object_t *random_obj = create_random_ucl_object();
    
    bool copy = Data[0] % 2 == 0;

    // Fuzz ucl_array_merge
    ucl_array_merge(top, elt, copy);

    // Fuzz ucl_array_delete
    ucl_object_t *deleted = ucl_array_delete(top, random_obj);
    if (deleted) {
        ucl_object_unref(deleted);
    }

    // Fuzz ucl_array_pop_first
    ucl_object_t *popped_first = ucl_array_pop_first(top);
    if (popped_first) {
        ucl_object_unref(popped_first);
    }

    // Fuzz ucl_array_pop_last
    ucl_object_t *popped_last = ucl_array_pop_last(top);
    if (popped_last) {
        ucl_object_unref(popped_last);
    }

    // Fuzz ucl_elt_append
    ucl_object_t *new_head = ucl_elt_append(top, random_obj);
    if (new_head != top && new_head != NULL) {
        ucl_object_unref(new_head);
    }

    // Fuzz ucl_array_append
    ucl_array_append(top, random_obj);

    // Cleanup
    ucl_object_unref(elt);
    ucl_object_unref(random_obj);

    // Ensure we only unref top once
    if (new_head != top) {
        ucl_object_unref(top);
    }

    return 0;
}