// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_lookup_any at ucl_util.c:2683:1 in ucl.h
// ucl_object_delete_keyl at ucl_util.c:2482:6 in ucl.h
// ucl_object_reserve at ucl_util.c:3026:6 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_delete_key at ucl_util.c:2503:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static ucl_object_t *create_dummy_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        memset(obj, 0, sizeof(ucl_object_t));
        obj->type = UCL_OBJECT;
        obj->key = strdup("dummy_key");
        obj->keylen = strlen(obj->key);
    }
    return obj;
}

static void cleanup_ucl_object(ucl_object_t *obj) {
    if (obj) {
        if (obj->key) {
            free((void *)obj->key);
        }
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ucl_object_t *ucl_obj = create_dummy_ucl_object();
    if (!ucl_obj) {
        return 0;
    }

    // Ensure the key is null-terminated
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cleanup_ucl_object(ucl_obj);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Fuzz ucl_object_type
    ucl_type_t type = ucl_object_type(ucl_obj);

    // Fuzz ucl_object_lookup_any
    const ucl_object_t *found_obj = ucl_object_lookup_any(ucl_obj, key, "alternative_key", NULL);

    // Fuzz ucl_object_delete_keyl
    bool delete_keyl_result = ucl_object_delete_keyl(ucl_obj, key, Size);

    // Fuzz ucl_object_reserve
    size_t reserved_size = Data[0];
    bool reserve_result = ucl_object_reserve(ucl_obj, reserved_size);

    // Fuzz ucl_object_replace_key
    ucl_object_t *new_obj = create_dummy_ucl_object();
    if (new_obj) {
        bool replace_key_result = ucl_object_replace_key(ucl_obj, new_obj, key, Size, true);
    }

    // Fuzz ucl_object_delete_key
    bool delete_key_result = ucl_object_delete_key(ucl_obj, key);

    // Cleanup new_obj after all operations
    if (new_obj) {
        cleanup_ucl_object(new_obj);
    }

    cleanup_ucl_object(ucl_obj);
    free(key);
    return 0;
}