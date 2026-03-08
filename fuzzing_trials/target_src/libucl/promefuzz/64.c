// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_pop_first at ucl_util.c:3303:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_tail at ucl_util.c:3271:1 in ucl.h
// ucl_array_index_of at ucl_util.c:3355:1 in ucl.h
// ucl_array_pop_last at ucl_util.c:3283:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_head at ucl_util.c:3258:1 in ucl.h
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
#include <stdlib.h>
#include <stdio.h>

static ucl_object_t* create_random_ucl_array(const uint8_t *Data, size_t Size) {
    ucl_object_t *array = ucl_object_new();
    array->type = UCL_ARRAY;

    for (size_t i = 0; i < Size; i++) {
        ucl_object_t *elt = ucl_object_new();
        elt->type = UCL_INT;
        elt->value.iv = Data[i];
        ucl_array_append(array, elt);
    }

    return array;
}

static ucl_object_t* create_random_ucl_object(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int64_t)) return NULL;

    ucl_object_t *obj = ucl_object_new();
    obj->type = UCL_INT;
    obj->value.iv = *((int64_t*)Data);

    return obj;
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *array = create_random_ucl_array(Data, Size);
    ucl_object_t *obj = create_random_ucl_object(Data, Size);

    if (array && obj) {
        ucl_object_t *removed_elt = ucl_array_delete(array, obj);
        if (removed_elt) {
            ucl_object_unref(removed_elt);
        }

        ucl_object_t *first_elt = ucl_array_pop_first(array);
        if (first_elt) {
            ucl_object_unref(first_elt);
        }

        const ucl_object_t *last_elt = ucl_array_tail(array);

        unsigned int index = ucl_array_index_of(array, obj);

        ucl_object_t *last_popped_elt = ucl_array_pop_last(array);
        if (last_popped_elt) {
            ucl_object_unref(last_popped_elt);
        }

        const ucl_object_t *head_elt = ucl_array_head(array);
    }

    if (array) {
        ucl_object_unref(array);
    }
    if (obj) {
        ucl_object_unref(obj);
    }

    return 0;
}