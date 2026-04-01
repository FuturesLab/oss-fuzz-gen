// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_pop_key at ucl_util.c:2528:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_delete_keyl at ucl_util.c:2482:6 in ucl.h
// ucl_object_lookup_len at ucl_util.c:2656:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key_merged at ucl_util.c:2539:6 in ucl.h
// ucl_object_delete_key at ucl_util.c:2503:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ucl.h>

static ucl_object_t* create_test_object() {
    ucl_object_t *obj = ucl_object_new();
    if (!obj) return NULL;

    ucl_object_t *nested_obj = ucl_object_fromstring("value");
    ucl_object_insert_key(obj, nested_obj, "key", 3, false);

    return obj;
}

int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a null-terminated key
    char key[Size + 1];
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Create a test UCL object
    ucl_object_t *top = create_test_object();
    if (!top) return 0;

    // Fuzz ucl_object_pop_key
    ucl_object_t *popped_obj = ucl_object_pop_key(top, key);
    if (popped_obj) {
        ucl_object_unref(popped_obj);
    }

    // Fuzz ucl_object_delete_keyl
    bool delete_keyl_result = ucl_object_delete_keyl(top, key, Size);

    // Fuzz ucl_object_lookup_len
    const ucl_object_t *lookup_obj = ucl_object_lookup_len(top, key, Size);

    // Fuzz ucl_object_replace_key
    ucl_object_t *new_obj = ucl_object_fromstring("new_value");
    bool replace_key_result = ucl_object_replace_key(top, new_obj, key, Size, true);

    // Fuzz ucl_object_insert_key_merged
    ucl_object_t *merge_obj = ucl_object_fromstring("merge_value");
    bool insert_key_merged_result = ucl_object_insert_key_merged(top, merge_obj, key, Size, true);

    // Fuzz ucl_object_delete_key
    bool delete_key_result = ucl_object_delete_key(top, key);

    // Cleanup
    ucl_object_unref(top);

    return 0;
}