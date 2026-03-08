// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_ref at ucl_util.c:3591:1 in ucl.h
// ucl_object_lookup_path_char at ucl_util.c:2926:1 in ucl.h
// ucl_object_tolstring at ucl_util.c:3566:1 in ucl.h
// ucl_object_tostring at ucl_util.c:3527:1 in ucl.h
// ucl_copy_value_trash at ucl_util.c:546:1 in ucl.h
// ucl_object_tostring_forced at ucl_util.c:3536:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ucl.h"

static ucl_object_t *create_dummy_ucl_object() {
    ucl_object_t *obj = malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->value.ov = NULL; // Initialize to NULL to prevent invalid access
        obj->key = "dummy_key";
        obj->next = NULL;
        obj->prev = NULL;
        obj->keylen = strlen(obj->key);
        obj->len = 0;
        obj->ref = 1;
        obj->flags = 0;
        obj->type = 0;
        memset(obj->trash_stack, 0, sizeof(obj->trash_stack));
    }
    return obj;
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *obj = create_dummy_ucl_object();
    if (!obj) return 0;

    // Test ucl_object_ref
    ucl_object_t *ref_obj = ucl_object_ref(obj);
    if (ref_obj == NULL) {
        free(obj);
        return 0;
    }

    // Test ucl_object_lookup_path_char
    const char *path = "dummy_key";
    char sep = '.';
    const ucl_object_t *found_obj = ucl_object_lookup_path_char(obj, path, sep);

    // Test ucl_object_tolstring
    size_t tlen;
    const char *tolstring = ucl_object_tolstring(obj, &tlen);

    // Test ucl_object_tostring
    const char *tostring = ucl_object_tostring(obj);

    // Test ucl_copy_value_trash
    char *copied_value = ucl_copy_value_trash(obj);

    // Test ucl_object_tostring_forced
    const char *tostring_forced = ucl_object_tostring_forced(obj);

    // Cleanup
    if (copied_value) {
        free(copied_value);
    }
    free(obj);

    return 0;
}