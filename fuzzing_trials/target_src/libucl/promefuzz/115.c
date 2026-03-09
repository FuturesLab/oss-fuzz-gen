// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_ref at ucl_util.c:3591:1 in ucl.h
// ucl_object_compare at ucl_util.c:3711:5 in ucl.h
// ucl_object_copy at ucl_util.c:3692:1 in ucl.h
// ucl_object_array_sort at ucl_util.c:3799:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "ucl.h"

static ucl_object_t* create_random_ucl_object(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_object_t)) {
        return NULL;
    }

    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (!obj) {
        return NULL;
    }

    memset(obj, 0, sizeof(ucl_object_t)); // Initialize all fields to zero

    obj->value.iv = *(int64_t *)Data;
    obj->key = NULL; // Avoid using arbitrary data as a string
    obj->keylen = 0;
    obj->type = UCL_INT; // Default type, can be randomized further
    obj->ref = 1;

    return obj;
}

static void free_ucl_object(ucl_object_t *obj) {
    if (obj && obj->ref == 1) {
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    ucl_object_t *obj1 = create_random_ucl_object(Data, Size);
    ucl_object_t *obj2 = create_random_ucl_object(Data, Size);

    if (obj1) {
        // Test ucl_object_type
        ucl_type_t type = ucl_object_type(obj1);

        // Test ucl_object_ref
        ucl_object_t *ref_obj = ucl_object_ref(obj1);

        // Test ucl_object_compare
        if (obj2) {
            int cmp_result = ucl_object_compare(obj1, obj2);
        }

        // Test ucl_object_copy
        ucl_object_t *copy_obj = ucl_object_copy(obj1);

        // Test ucl_object_array_sort
        ucl_object_array_sort(obj1, ucl_object_compare_qsort);

        // Clean up
        free_ucl_object(copy_obj);
        if (ref_obj != obj1) {
            free_ucl_object(ref_obj);
        }
    }

    free_ucl_object(obj1);
    free_ucl_object(obj2);

    return 0;
}