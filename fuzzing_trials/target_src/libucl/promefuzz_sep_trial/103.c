// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_object_iter_chk_excpn at ucl_util.c:2809:6 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
// ucl_object_iterate_with_error at ucl_util.c:2717:1 in ucl.h
// ucl_object_iterate_reset at ucl_util.c:2819:1 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

static void initialize_ucl_object(ucl_object_t *obj) {
    obj->type = UCL_OBJECT;
    obj->value.ov = NULL; // Normally, this would point to a valid object or hash table
    obj->key = NULL;
    obj->next = NULL;
    obj->prev = NULL;
    obj->keylen = 0;
    obj->len = 0;
    obj->ref = 1;
    obj->flags = 0;
}

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(ucl_object_t)) {
        return 0;
    }

    ucl_object_t obj;
    initialize_ucl_object(&obj);

    ucl_object_iter_t iter = ucl_object_iterate_new(&obj);
    if (iter == NULL) {
        return 0;
    }

    bool expand_values = (Data[0] % 2 == 0);
    const ucl_object_t *next_obj = ucl_object_iterate_safe(iter, expand_values);

    // Correctly pass the iterator by value, not by reference
    if (ucl_object_iter_chk_excpn(iter)) {
        ucl_object_iterate_free(iter);
        return 0;
    }

    int error = 0;
    const ucl_object_t *error_obj = ucl_object_iterate_with_error(&obj, &iter, expand_values, &error);

    iter = ucl_object_iterate_reset(iter, next_obj);

    ucl_object_iterate_free(iter);

    return 0;
}