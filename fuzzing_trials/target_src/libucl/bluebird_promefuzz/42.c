#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static ucl_object_t *create_random_ucl_object() {
    ucl_object_t *obj = malloc(sizeof(ucl_object_t));
    if (obj == NULL) {
        return NULL;
    }
    obj->key = NULL;
    obj->value.iv = 0;
    obj->next = NULL;
    obj->prev = NULL;
    obj->keylen = 0;
    obj->len = 0;
    obj->ref = 1;
    obj->flags = 0;
    obj->type = 0;
    memset(obj->trash_stack, 0, sizeof(obj->trash_stack));
    return obj;
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy UCL object
    ucl_object_t *top = create_random_ucl_object();
    if (!top) return 0;

    // Create a key for deletion
    const char *key = (const char *)Data;
    size_t keylen = Size;

    // Test ucl_object_delete_keyl
    bool result = ucl_object_delete_keyl(top, key, keylen);

    // Create another UCL object for array operations
    ucl_object_t *elt = create_random_ucl_object();
    if (!elt) {
        ucl_object_free(top);
        return 0;
    }

    // Test ucl_array_replace_index
    unsigned int index = Data[0] % 10;  // Random index
    ucl_object_t *replaced = ucl_array_replace_index(top, elt, index);
    if (replaced) {
        ucl_object_unref(replaced);
    }

    // Test ucl_object_ref
    ucl_object_t *ref_obj = ucl_object_ref(top);

    // Test ucl_object_copy
    ucl_object_t *copy_obj = ucl_object_copy(top);
    if (copy_obj) {
        ucl_object_unref(copy_obj);
    }

    // Test ucl_array_delete
    ucl_object_t *deleted = ucl_array_delete(top, elt);
    if (deleted) {
        ucl_object_unref(deleted);
    }

    // Cleanup
    ucl_object_unref(ref_obj);
    ucl_object_unref(elt);
    ucl_object_free(top);

    return 0;
}