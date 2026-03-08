// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_object_iter_chk_excpn at ucl_util.c:2809:6 in ucl.h
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static ucl_object_t* create_dummy_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->type = UCL_OBJECT;
        obj->value.ov = NULL;
        obj->key = NULL;
        obj->len = 0;
        obj->ref = 1;
        obj->trash_stack[0] = NULL;
        obj->trash_stack[1] = NULL;
    }
    return obj;
}

static ucl_object_t* create_dummy_array() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->type = UCL_ARRAY;
        obj->value.av = NULL;
        obj->key = NULL;
        obj->len = 0;
        obj->ref = 1;
        obj->trash_stack[0] = NULL;
        obj->trash_stack[1] = NULL;
    }
    return obj;
}

int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *obj = create_dummy_object();
    ucl_object_t *array = create_dummy_array();
    ucl_object_t *element = create_dummy_object();
    ucl_object_iter_t iter = NULL;

    if (obj && array && element) {
        // Initialize iterator properly
        iter = ucl_object_iterate_new(obj);

        // Test ucl_object_iterate_safe
        const ucl_object_t *next_obj = ucl_object_iterate_safe(iter, Data[0] % 2);

        // Check for exceptions after iteration only if iter is valid
        if (iter != NULL) {
            bool exception_occurred = ucl_object_iter_chk_excpn(iter);
        }

        // Test ucl_array_replace_index
        unsigned int index = Data[0] % 10;
        ucl_object_t *replaced_obj = ucl_array_replace_index(array, element, index);

        // Test ucl_array_delete
        ucl_object_t *deleted_obj = ucl_array_delete(array, element);

        // Ensure the key is null-terminated and within bounds
        size_t keylen = (Size > 1) ? Size - 1 : 0;
        char *key = (char *)malloc(keylen + 1);
        if (key) {
            memcpy(key, Data, keylen);
            key[keylen] = '\0';

            // Test ucl_object_replace_key
            bool replace_key_result = ucl_object_replace_key(obj, element, key, keylen, Data[0] % 2);

            free(key);
        }

        // Test ucl_array_append
        bool append_result = ucl_array_append(array, element);

        // Cleanup replaced and deleted objects
        if (replaced_obj) {
            free(replaced_obj);
        }
        if (deleted_obj) {
            free(deleted_obj);
        }

        // Cleanup iterator
        ucl_object_iterate_free(iter);
    }

    // Cleanup
    if (obj) free(obj);
    if (array) free(array);
    if (element) free(element);

    return 0;
}