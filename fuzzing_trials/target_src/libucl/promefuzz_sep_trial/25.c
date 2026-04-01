// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_todouble at ucl_util.c:3446:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_frombool at ucl_util.c:3118:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static ucl_object_t *create_dummy_ucl_object() {
    ucl_object_t *obj = ucl_object_typed_new(UCL_FLOAT);
    if (obj) {
        obj->value.dv = 42.0; // Set a default double value
        obj->ref = 1; // Initialize reference count
    }
    return obj;
}

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment
    ucl_object_t *obj = create_dummy_ucl_object();
    if (obj == NULL) {
        return 0; // Memory allocation failed, exit early
    }

    // Step 2: Invoke `ucl_object_todouble`
    double result = ucl_object_todouble(obj);

    // Step 3: Cleanup using `ucl_object_unref`
    ucl_object_unref(obj);

    // Step 4: Use `ucl_object_frombool`
    bool bool_val = (Size > 0 && Data[0] % 2 == 0);
    ucl_object_t *bool_obj = ucl_object_frombool(bool_val);
    if (bool_obj == NULL) {
        return 0; // Failed to create boolean object, exit early
    }

    // Step 5: Use `ucl_object_insert_key`
    const char *key = "example_key";
    size_t keylen = strlen(key);
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    if (top == NULL) {
        ucl_object_unref(bool_obj);
        return 0; // Memory allocation failed, exit early
    }

    bool insert_result = ucl_object_insert_key(top, bool_obj, key, keylen, true);

    // Step 6: Cleanup
    ucl_object_unref(top); // This will also unref bool_obj if inserted successfully

    return 0;
}