// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_delete_key at ucl_util.c:2503:6 in ucl.h
// ucl_object_lookup at ucl_util.c:2673:1 in ucl.h
// ucl_object_insert_key_merged at ucl_util.c:2539:6 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ucl.h"

static ucl_object_t *create_random_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        memset(obj, 0, sizeof(ucl_object_t));
        obj->type = UCL_OBJECT;
    }
    return obj;
}

static void free_ucl_object(ucl_object_t *obj) {
    if (obj) {
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy UCL objects
    ucl_object_t *top = create_random_ucl_object();
    ucl_object_t *elt = create_random_ucl_object();
    ucl_object_t *replace_elt = create_random_ucl_object();
    ucl_object_t *merged_elt = create_random_ucl_object();

    if (!top || !elt || !replace_elt || !merged_elt) {
        free_ucl_object(top);
        free_ucl_object(elt);
        free_ucl_object(replace_elt);
        free_ucl_object(merged_elt);
        return 0;
    }

    // Prepare a key
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        free_ucl_object(top);
        free_ucl_object(elt);
        free_ucl_object(replace_elt);
        free_ucl_object(merged_elt);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0'; // Ensure null-termination
    size_t keylen = Size;
    bool copy_key = Data[0] % 2 == 0;

    // Test ucl_object_insert_key
    ucl_object_insert_key(top, elt, key, keylen, copy_key);

    // Test ucl_object_replace_key
    ucl_object_replace_key(top, replace_elt, key, keylen, copy_key);

    // Test ucl_object_delete_key
    ucl_object_delete_key(top, key);

    // Test ucl_object_lookup
    ucl_object_lookup(top, key);

    // Test ucl_object_insert_key_merged
    ucl_object_insert_key_merged(top, merged_elt, key, keylen, copy_key);

    // Test ucl_object_pop_key
    ucl_object_t *popped = ucl_object_pop_key(top, key);
    if (popped && popped != elt && popped != replace_elt && popped != merged_elt) {
        free_ucl_object(popped);
    }

    // Cleanup
    free(key);
    free_ucl_object(top);
    free_ucl_object(elt);
    free_ucl_object(replace_elt);
    free_ucl_object(merged_elt);

    return 0;
}