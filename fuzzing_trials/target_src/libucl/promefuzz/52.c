// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_copy_key_trash at ucl_util.c:494:1 in ucl.h
// ucl_object_pop_keyl at ucl_util.c:2509:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_keyl at ucl_util.c:3581:1 in ucl.h
// ucl_object_key at ucl_util.c:3575:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ucl.h>

static ucl_object_t *create_ucl_object(const char *key, const char *value) {
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);
    if (obj) {
        ucl_object_insert_key(obj, ucl_object_fromstring(value), key, 0, false);
    }
    return obj;
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a UCL object
    ucl_object_t *top = create_ucl_object("key", "value");

    // Test ucl_copy_key_trash
    char *copied_key = ucl_copy_key_trash(top);
    if (copied_key) {
        // Do something with copied_key
    }

    // Test ucl_object_pop_keyl
    ucl_object_t *popped_obj = ucl_object_pop_keyl(top, "key", strlen("key"));
    if (popped_obj) {
        // Do something with popped_obj
        ucl_object_unref(popped_obj);
    }

    // Test ucl_object_insert_key
    ucl_object_t *elt = create_ucl_object("new_key", "new_value");
    bool insert_result = ucl_object_insert_key(top, elt, "insert_key", 0, true);

    // Test ucl_object_replace_key
    ucl_object_t *replace_elt = create_ucl_object("replace_key", "replace_value");
    bool replace_result = ucl_object_replace_key(top, replace_elt, "replace_key", 0, true);

    // Test ucl_object_keyl
    size_t key_length;
    const char *keyl = ucl_object_keyl(top, &key_length);
    if (keyl) {
        // Do something with keyl
    }

    // Test ucl_object_key
    const char *key = ucl_object_key(top);
    if (key) {
        // Do something with key
    }

    // Cleanup
    ucl_object_unref(top);

    return 0;
}