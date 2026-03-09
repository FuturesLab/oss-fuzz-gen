// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_validate at ucl_schema.c:1068:6 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
// ucl_object_sort_keys at ucl_util.c:3812:6 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_full at ucl_util.c:2845:1 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
// ucl_object_iterate_with_error at ucl_util.c:2717:1 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ucl.h>

static ucl_object_t *create_random_ucl_object(const uint8_t *data, size_t size) {
    ucl_object_t *obj = calloc(1, sizeof(ucl_object_t));
    if (obj && size > 0) {
        obj->key = (const char *)data;
        obj->keylen = (uint32_t)size;
    }
    return obj;
}

static char *create_null_terminated_string(const uint8_t *data, size_t size) {
    char *str = malloc(size + 1);
    if (str) {
        memcpy(str, data, size);
        str[size] = '\0';
    }
    return str;
}

int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size) {
    struct ucl_schema_error err;
    ucl_object_t *schema = create_random_ucl_object(Data, Size);
    ucl_object_t *obj = create_random_ucl_object(Data, Size);
    ucl_object_t *top = create_random_ucl_object(Data, Size);
    ucl_object_t *elt = create_random_ucl_object(Data, Size);
    char *key = create_null_terminated_string(Data, Size);
    ucl_object_iter_t iter = NULL;
    int ep;

    if (schema && obj) {
        ucl_object_validate(schema, obj, &err);
    }

    if (top && key) {
        ucl_object_pop_key(top, key);
    }

    if (obj) {
        ucl_object_sort_keys(obj, UCL_SORT_KEYS_DEFAULT);
    }

    // Ensure iter is properly initialized
    if (obj) {
        iter = ucl_object_iterate_new(obj);
        if (iter) {
            ucl_object_iterate_full(iter, UCL_ITERATE_EXPLICIT);
            ucl_object_iterate_free(iter);
        }
    }

    if (obj) {
        iter = NULL;
        ucl_object_iterate_with_error(obj, &iter, true, &ep);
    }

    if (top && elt && key) {
        ucl_object_replace_key(top, elt, key, strlen(key), true);
    }

    free(schema);
    free(obj);
    free(top);
    free(elt);
    free(key);
    
    return 0;
}