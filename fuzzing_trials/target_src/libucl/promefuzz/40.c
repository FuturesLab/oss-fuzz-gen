// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_merge at ucl_util.c:2551:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
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
#include "ucl.h"

static ucl_object_t* create_ucl_object(ucl_type_t type, const char *key) {
    ucl_object_t *obj = ucl_object_new_full(type, 0);
    if (obj) {
        obj->key = key;
        obj->keylen = key ? strlen(key) : 0;
    }
    return obj;
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create UCL objects
    ucl_object_t *obj1 = create_ucl_object(UCL_OBJECT, "key1");
    ucl_object_t *obj2 = create_ucl_object(UCL_OBJECT, "key2");

    if (!obj1 || !obj2) {
        if (obj1) ucl_object_unref(obj1);
        if (obj2) ucl_object_unref(obj2);
        return 0;
    }

    // Merge obj2 into obj1
    bool merge_result = ucl_object_merge(obj1, obj2, true);

    // Unref obj2
    ucl_object_unref(obj2);

    // Create a new UCL object with type and priority
    ucl_object_t *new_obj = ucl_object_new_full(UCL_ARRAY, 0);

    if (new_obj) {
        // Append new_obj to obj1
        bool append_result = ucl_array_append(obj1, new_obj);

        // Cleanup
        ucl_object_unref(new_obj);
    }

    ucl_object_unref(obj1);

    return 0;
}