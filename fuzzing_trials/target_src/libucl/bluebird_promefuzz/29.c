#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ucl.h"

static ucl_object_t *create_random_ucl_object(const uint8_t *Data, size_t Size) {
    ucl_object_t *obj = malloc(sizeof(ucl_object_t));
    if (!obj) return NULL;

    size_t offset = 0;
    if (Size > sizeof(int64_t)) {
        obj->value.iv = *((int64_t *)(Data + offset));
        offset += sizeof(int64_t);
    } else {
        obj->value.iv = 0;
    }

    if (Size > offset + sizeof(double)) {
        obj->value.dv = *((double *)(Data + offset));
        offset += sizeof(double);
    } else {
        obj->value.dv = 0.0;
    }

    if (Size > offset) {
        obj->value.sv = (const char *)(Data + offset);
        obj->len = Size - offset;
    } else {
        obj->value.sv = NULL;
        obj->len = 0;
    }

    obj->key = NULL;
    obj->next = NULL;
    obj->prev = NULL;
    obj->keylen = 0;
    obj->ref = 1;
    obj->flags = 0;
    obj->type = 0;
    memset(obj->trash_stack, 0, sizeof(obj->trash_stack));

    return obj;
}

static void free_ucl_object(ucl_object_t *obj) {
    if (obj) {
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    ucl_object_t *obj = create_random_ucl_object(Data, Size);
    if (!obj) return 0;

    const char *str;
    char *copy_str;
    double dbl;
    size_t len;

    // Test ucl_object_tostring_forced
    str = ucl_object_tostring_forced(obj);
    if (str) {
        // Simulate usage
        (void)strlen(str);
    }

    // Test ucl_object_ref
    ucl_object_t *ref_obj = ucl_object_ref(obj);
    if (ref_obj) {
        // Simulate usage
        (void)ref_obj->ref;
    }

    // Test ucl_object_todouble
    dbl = ucl_object_todouble(obj);
    (void)dbl; // Simulate usage

    // Test ucl_object_tolstring
    str = ucl_object_tolstring(obj, &len);
    if (str) {
        // Simulate usage
        (void)strlen(str);
    }

    // Test ucl_object_tostring
    str = ucl_object_tostring(obj);
    if (str) {
        // Simulate usage
        (void)strlen(str);
    }

    // Test ucl_copy_value_trash
    copy_str = ucl_copy_value_trash(obj);
    if (copy_str) {
        // Simulate usage
        free(copy_str);
    }

    free_ucl_object(obj);
    return 0;
}