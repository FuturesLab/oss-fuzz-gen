// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_ref at ucl_util.c:3591:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_copy_key_trash at ucl_util.c:494:1 in ucl.h
// ucl_object_tolstring at ucl_util.c:3566:1 in ucl.h
// ucl_copy_value_trash at ucl_util.c:546:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ucl.h"

static ucl_object_t *create_random_ucl_object(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;

    ucl_object_t *obj = ucl_object_new();
    if (!obj) return NULL;

    obj->key = (const char *)Data;
    obj->keylen = Size;

    switch (Data[0] % 3) {
        case 0:
            obj->value.iv = (int64_t)Data[0];
            obj->type = 0;
            break;
        case 1:
            obj->value.sv = (const char *)Data;
            obj->type = 1;
            break;
        case 2:
            obj->value.dv = (double)Data[0];
            obj->type = 2;
            break;
    }
    return obj;
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    ucl_object_t *obj = create_random_ucl_object(Data, Size);
    if (!obj) return 0;

    // Test ucl_object_ref
    ucl_object_t *ref_obj = ucl_object_ref(obj);

    // Test ucl_object_todouble
    double dbl_value = ucl_object_todouble(obj);

    // Test ucl_copy_key_trash
    char *key_copy = ucl_copy_key_trash(obj);
    if (key_copy) {
        free(key_copy);
    }

    // Test ucl_object_tolstring
    size_t tlen;
    const char *str_value = ucl_object_tolstring(obj, &tlen);

    // Test ucl_copy_value_trash
    char *value_copy = ucl_copy_value_trash(obj);
    if (value_copy) {
        free(value_copy);
    }

    // Cleanup
    // Only free the original object since ucl_object_ref does not allocate new memory
    free(obj);

    return 0;
}