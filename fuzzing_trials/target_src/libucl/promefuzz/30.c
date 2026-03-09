// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_lookup_any at ucl_util.c:2683:1 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
// ucl_object_delete_keyl at ucl_util.c:2482:6 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_delete_key at ucl_util.c:2503:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

static ucl_object_t* create_dummy_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->key = "dummy_key";
        obj->value.sv = "dummy_value";
        obj->keylen = strlen(obj->key);
        obj->ref = 1;
    }
    return obj;
}

static void free_ucl_object(ucl_object_t *obj) {
    if (obj) {
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *top = create_dummy_ucl_object();
    ucl_object_t *elt = create_dummy_ucl_object();
    if (!top || !elt) {
        free_ucl_object(top);
        free_ucl_object(elt);
        return 0;
    }

    const char *key = "key";
    size_t keylen = strlen(key);
    bool copy_key = true;

    // Test ucl_object_insert_key
    bool insert_result = ucl_object_insert_key(top, elt, key, keylen, copy_key);

    // Test ucl_object_lookup_any
    const ucl_object_t *lookup_result = ucl_object_lookup_any(top, key, "alternative_key", NULL);

    // Test ucl_object_pop_key
    ucl_object_t *popped_obj = ucl_object_pop_key(top, key);

    // Test ucl_object_delete_keyl
    bool delete_keyl_result = ucl_object_delete_keyl(top, key, keylen);

    // Test ucl_object_replace_key
    bool replace_result = ucl_object_replace_key(top, elt, key, keylen, copy_key);

    // Test ucl_object_delete_key
    bool delete_key_result = ucl_object_delete_key(top, key);

    // Cleanup
    free_ucl_object(top);
    free_ucl_object(elt);
    free_ucl_object(popped_obj);

    return 0;
}