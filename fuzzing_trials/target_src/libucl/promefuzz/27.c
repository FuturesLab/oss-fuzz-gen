// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_lookup at ucl_util.c:2673:1 in ucl.h
// ucl_object_lookup_len at ucl_util.c:2656:1 in ucl.h
// ucl_object_delete_keyl at ucl_util.c:2482:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static void initialize_ucl_object(ucl_object_t *obj, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        obj->key = (const char *)Data;
        obj->keylen = (uint32_t)Size;
        obj->type = UCL_OBJECT;
    } else {
        obj->key = NULL;
        obj->keylen = 0;
        obj->type = UCL_NULL;
    }
}

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Initialize UCL object
    ucl_object_t parent_obj;
    initialize_ucl_object(&parent_obj, Data, Size);

    // Ensure the data is null-terminated for safe string operations
    char *key = (char *)malloc(Size + 1);
    if (key == NULL) {
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Create a new UCL object
    ucl_object_t *new_obj = ucl_object_typed_new(UCL_OBJECT);
    if (new_obj == NULL) {
        free(key);
        return 0;
    }

    // Attempt to look up an object with a key
    const ucl_object_t *looked_up_obj = ucl_object_lookup(&parent_obj, key);

    // Attempt to look up an object with a key and length
    const ucl_object_t *looked_up_len_obj = ucl_object_lookup_len(&parent_obj, key, Size);

    // Attempt to delete a key from the object
    bool delete_success = ucl_object_delete_keyl(new_obj, key, Size);

    // Cleanup
    free(key);
    free(new_obj);

    return 0;
}