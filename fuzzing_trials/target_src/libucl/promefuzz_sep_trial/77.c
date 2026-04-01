// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_set_include_path at ucl_parser.c:3180:6 in ucl.h
// ucl_object_fromint at ucl_util.c:3090:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

static ucl_object_t* create_sample_ucl_array() {
    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
    for (int i = 0; i < 5; i++) {
        ucl_object_t *element = ucl_object_fromint(i);
        ucl_array_append(array, element);
    }
    return array;
}

static ucl_object_t* create_sample_ucl_object() {
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *key1 = ucl_object_fromstring("value1");
    ucl_object_insert_key(obj, key1, "key1", 0, false);
    return obj;
}

int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    // Initialize UCL objects
    ucl_object_t *array = create_sample_ucl_array();
    ucl_object_t *obj = create_sample_ucl_object();
    
    // ucl_object_iterate_safe
    ucl_object_iter_t iter = ucl_object_iterate_new(obj);
    while (ucl_object_iterate_safe(iter, true)) {
        // Do nothing, just iterate
    }
    ucl_object_iterate_free(iter);

    // ucl_array_replace_index
    if (Size > 0) {
        ucl_object_t *new_element = ucl_object_fromint(Data[0]);
        ucl_object_t *replaced = ucl_array_replace_index(array, new_element, 2);
        if (replaced) {
            ucl_object_unref(replaced);
        }
    }

    // ucl_array_delete
    if (Size > 1) {
        ucl_object_t *element_to_remove = ucl_object_fromint(Data[1]);
        ucl_object_t *removed = ucl_array_delete(array, element_to_remove);
        if (removed) {
            ucl_object_unref(removed);
        }
        ucl_object_unref(element_to_remove);
    }

    // ucl_array_prepend
    if (Size > 2) {
        ucl_object_t *element_to_prepend = ucl_object_fromint(Data[2]);
        ucl_array_prepend(array, element_to_prepend);
    }

    // ucl_set_include_path
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_set_include_path(parser, array);

    // ucl_array_append
    if (Size > 3) {
        ucl_object_t *element_to_append = ucl_object_fromint(Data[3]);
        ucl_array_append(array, element_to_append);
    }

    // Cleanup
    ucl_object_unref(array);
    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}