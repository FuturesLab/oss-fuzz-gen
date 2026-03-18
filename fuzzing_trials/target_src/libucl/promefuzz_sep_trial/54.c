// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_pop_first at ucl_util.c:3303:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_index_of at ucl_util.c:3355:1 in ucl.h
// ucl_array_pop_last at ucl_util.c:3283:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_array_sort at ucl_util.c:3799:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ucl.h"

static ucl_object_t *create_random_ucl_object() {
    ucl_object_t *obj = ucl_object_typed_new(UCL_ARRAY);
    return obj;
}

static int compare_ucl_objects(const ucl_object_t **o1, const ucl_object_t **o2) {
    if ((*o1)->value.iv < (*o2)->value.iv) return -1;
    if ((*o1)->value.iv > (*o2)->value.iv) return 1;
    return 0;
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;
    
    ucl_object_t *array = create_random_ucl_object();
    ucl_object_t *element = ucl_object_fromint(Data[0]);
    if (!array || !element) {
        if (array) ucl_object_unref(array);
        if (element) ucl_object_unref(element);
        return 0;
    }

    unsigned int index = Data[0] % (Size + 1); // To ensure index is within bounds

    ucl_object_t *replaced = ucl_array_replace_index(array, element, index);
    if (replaced) {
        ucl_object_unref(replaced);
    }

    ucl_object_t *deleted = ucl_array_delete(array, element);
    if (deleted) {
        ucl_object_unref(deleted);
    }

    ucl_object_t *popped_first = ucl_array_pop_first(array);
    if (popped_first) {
        ucl_object_unref(popped_first);
    }

    unsigned int found_index = ucl_array_index_of(array, element);

    ucl_object_t *popped_last = ucl_array_pop_last(array);
    if (popped_last) {
        ucl_object_unref(popped_last);
    }

    ucl_object_array_sort(array, compare_ucl_objects);

    ucl_object_unref(array);
    ucl_object_unref(element);

    return 0;
}