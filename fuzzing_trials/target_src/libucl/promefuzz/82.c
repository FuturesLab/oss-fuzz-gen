// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_set_include_path at ucl_parser.c:3180:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ucl.h>

static void initialize_ucl_object(ucl_object_t *obj, uint16_t type) {
    obj->type = type;
    obj->ref = 1;
    obj->next = NULL;
    obj->prev = NULL;
    obj->key = NULL;
    obj->keylen = 0;
    obj->len = 0;
    obj->flags = 0;
    obj->value.ud = NULL;
}

static ucl_object_t *create_ucl_array_object() {
    ucl_object_t *obj = ucl_object_typed_new(UCL_ARRAY);
    return obj;
}

static ucl_object_t *create_ucl_object_with_value(int64_t value) {
    ucl_object_t *obj = ucl_object_typed_new(UCL_INT);
    obj->value.iv = value;
    return obj;
}

int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize UCL objects
    ucl_object_t *array = create_ucl_array_object();
    ucl_object_t *element = create_ucl_object_with_value((int64_t)Data[0]);

    // Test ucl_array_append
    ucl_array_append(array, element);

    // Test ucl_array_prepend
    ucl_array_prepend(array, element);

    // Test ucl_array_replace_index
    ucl_object_t *replaced = ucl_array_replace_index(array, element, 0);
    if (replaced && replaced != element) {
        ucl_object_unref(replaced);
    }

    // Test ucl_array_delete
    ucl_object_t *deleted = ucl_array_delete(array, element);
    if (deleted && deleted != element) {
        ucl_object_unref(deleted);
    }

    // Test ucl_object_iterate_safe
    ucl_object_iter_t iter = ucl_object_iterate_new(array);
    const ucl_object_t *iterated_obj;
    while ((iterated_obj = ucl_object_iterate_safe(iter, true)) != NULL) {
        // Do nothing, just iterate
    }
    ucl_object_iterate_free(iter);

    // Test ucl_set_include_path
    struct ucl_parser *parser = ucl_parser_new(0);
    if (array->type == UCL_ARRAY) {
        ucl_set_include_path(parser, array);
    }
    ucl_parser_free(parser);

    // Cleanup
    if (replaced != element && deleted != element) {
        ucl_object_unref(element);
    }
    ucl_object_unref(array);

    return 0;
}