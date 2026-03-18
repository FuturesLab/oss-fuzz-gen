// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_ref at ucl_util.c:3591:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_copy_key_trash at ucl_util.c:494:1 in ucl.h
// ucl_object_tolstring at ucl_util.c:3566:1 in ucl.h
// ucl_copy_value_trash at ucl_util.c:546:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ucl.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    write_dummy_file(Data, Size);

    // Create a new UCL object
    ucl_object_t *obj = ucl_object_new();
    if (!obj) {
        return 0;
    }

    // Set up a fake key and value for the object
    obj->key = (const char *)Data;
    obj->keylen = Size;
    obj->value.sv = (const char *)Data;

    // Test ucl_object_ref
    ucl_object_t *ref_obj = ucl_object_ref(obj);

    // Test ucl_object_todouble
    double dval = ucl_object_todouble(obj);

    // Test ucl_copy_key_trash
    char *key_copy = ucl_copy_key_trash(obj);

    // Test ucl_object_tolstring
    size_t tlen = 0;
    const char *str_val = ucl_object_tolstring(obj, &tlen);

    // Test ucl_copy_value_trash
    char *value_copy = ucl_copy_value_trash(obj);

    // Clean up
    ucl_object_unref(ref_obj);
    ucl_object_unref(obj);

    // Do not free key_copy or value_copy as they are managed by the UCL library's trash stack

    return 0;
}