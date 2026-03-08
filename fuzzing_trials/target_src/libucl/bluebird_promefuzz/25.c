#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "ucl.h"

static ucl_object_t* create_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        memset(obj, 0, sizeof(ucl_object_t));
        obj->type = UCL_OBJECT;
        obj->value.ov = NULL; // Initialize the object value to NULL
    }
    return obj;
}

static char* copy_key(const uint8_t *Data, size_t Size) {
    char *key = (char *)malloc(Size + 1);
    if (key) {
        memcpy(key, Data, Size);
        key[Size] = '\0'; // Ensure the key is null-terminated
    }
    return key;
}

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *top = create_ucl_object();
    ucl_object_t *elt = create_ucl_object();
    if (!top || !elt) {
        free(top);
        free(elt);
        return 0;
    }

    char *key = copy_key(Data, Size);
    if (!key) {
        free(top);
        free(elt);
        return 0;
    }

    size_t keylen = Size;
    bool copy_key_flag = true;

    // Test ucl_object_insert_key
    ucl_object_insert_key(top, elt, key, keylen, copy_key_flag);

    // Test ucl_object_delete_keyl
    ucl_object_delete_keyl(top, key, keylen);

    // Test ucl_object_keyl
    size_t len;
    const char *retrieved_key = ucl_object_keyl(elt, &len);

    // Test ucl_object_replace_key
    ucl_object_replace_key(top, elt, key, keylen, copy_key_flag);

    // Test ucl_object_lookup_len
    const ucl_object_t *found_obj = ucl_object_lookup_len(top, key, keylen);

    // Test ucl_object_pop_keyl
    ucl_object_t *popped_obj = ucl_object_pop_keyl(top, key, keylen);
    if (popped_obj && popped_obj != elt) {
        free(popped_obj);
    }

    free(key);
    free(top);
    free(elt);

    return 0;
}