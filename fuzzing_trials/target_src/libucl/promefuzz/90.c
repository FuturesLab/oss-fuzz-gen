// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_lookup_len at ucl_util.c:2656:1 in ucl.h
// ucl_object_keyl at ucl_util.c:3581:1 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_pop_keyl at ucl_util.c:2509:1 in ucl.h
// ucl_object_delete_keyl at ucl_util.c:2482:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static ucl_object_t* create_ucl_object() {
    ucl_object_t *obj = ucl_object_new();
    if (obj) {
        obj->type = UCL_OBJECT;
    }
    return obj;
}

static void destroy_ucl_object(ucl_object_t *obj) {
    if (obj) {
        ucl_object_unref(obj);
    }
}

int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *top = create_ucl_object();
    if (!top) {
        return 0;
    }

    ucl_object_t *elt = create_ucl_object();
    if (!elt) {
        destroy_ucl_object(top);
        return 0;
    }

    const char *key = (const char *)Data;
    size_t keylen = Size;

    // Ensure key is null-terminated if keylen is 0
    char *null_terminated_key = NULL;
    if (keylen == 0) {
        null_terminated_key = malloc(Size + 1);
        if (null_terminated_key) {
            memcpy(null_terminated_key, Data, Size);
            null_terminated_key[Size] = '\0';
            key = null_terminated_key;
            keylen = 0;
        }
    }

    // Test ucl_object_insert_key
    bool inserted = ucl_object_insert_key(top, elt, key, keylen, true);
    if (inserted) {
        // Test ucl_object_lookup_len
        const ucl_object_t *found = ucl_object_lookup_len(top, key, keylen);
        if (found) {
            // Test ucl_object_keyl
            size_t len;
            const char *retrieved_key = ucl_object_keyl(found, &len);
        }

        // Test ucl_object_replace_key
        ucl_object_t *new_elt = create_ucl_object();
        if (new_elt) {
            bool replaced = ucl_object_replace_key(top, new_elt, key, keylen, true);
            if (replaced) {
                // Test ucl_object_pop_keyl
                ucl_object_t *popped = ucl_object_pop_keyl(top, key, keylen);
                if (popped) {
                    destroy_ucl_object(popped);
                }
            } else {
                destroy_ucl_object(new_elt);
            }
        }
    } else {
        destroy_ucl_object(elt);
    }

    // Test ucl_object_delete_keyl
    bool deleted = ucl_object_delete_keyl(top, key, keylen);

    if (null_terminated_key) {
        free(null_terminated_key);
    }

    destroy_ucl_object(top);
    return 0;
}