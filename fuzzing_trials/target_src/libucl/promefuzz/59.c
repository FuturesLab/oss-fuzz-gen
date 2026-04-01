// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_pop_first at ucl_util.c:3303:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_size at ucl_util.c:3323:1 in ucl.h
// ucl_array_find_index at ucl_util.c:3339:1 in ucl.h
// ucl_array_index_of at ucl_util.c:3355:1 in ucl.h
// ucl_array_pop_last at ucl_util.c:3283:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

static ucl_object_t *create_random_ucl_array(const uint8_t *Data, size_t Size) {
    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
    for (size_t i = 0; i < Size; i++) {
        ucl_object_t *obj = ucl_object_fromint(Data[i]);
        ucl_array_append(array, obj);
    }
    return array;
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ucl_object_t *array = create_random_ucl_array(Data, Size);

    // Fuzz ucl_array_replace_index
    ucl_object_t *new_element = ucl_object_fromint(Data[0]);
    unsigned int index = Data[0] % Size;
    ucl_object_t *replaced = ucl_array_replace_index(array, new_element, index);
    if (replaced) {
        ucl_object_unref(replaced);
    }

    // Fuzz ucl_array_pop_first
    ucl_object_t *first = ucl_array_pop_first(array);
    if (first) {
        ucl_object_unref(first);
    }

    // Fuzz ucl_array_size
    unsigned int size = ucl_array_size(array);

    // Fuzz ucl_array_find_index
    const ucl_object_t *found = ucl_array_find_index(array, index);

    // Fuzz ucl_array_index_of
    unsigned int index_of = ucl_array_index_of(array, new_element);

    // Fuzz ucl_array_pop_last
    ucl_object_t *last = ucl_array_pop_last(array);
    if (last) {
        ucl_object_unref(last);
    }

    // Cleanup
    ucl_object_unref(array);
    // new_element is already part of the array, no need to unref again

    return 0;
}