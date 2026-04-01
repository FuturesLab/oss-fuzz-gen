// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_new_full at ucl_util.c:2992:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_lookup_path at ucl_util.c:2919:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_object_delete_key at ucl_util.c:2503:6 in ucl.h
// ucl_object_reserve at ucl_util.c:3026:6 in ucl.h
// ucl_object_merge at ucl_util.c:2551:6 in ucl.h
// ucl_object_type at ucl_util.c:3068:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdbool.h>

static ucl_object_t *create_dummy_ucl_object() {
    ucl_object_t *obj = ucl_object_new();
    if (obj) {
        ucl_object_insert_key(obj, ucl_object_fromstring("value1"), "key1", 0, false);
        ucl_object_insert_key(obj, ucl_object_fromstring("value2"), "key2", 0, false);
    }
    return obj;
}

static ucl_object_t *create_dummy_ucl_array() {
    ucl_object_t *arr = ucl_object_new_full(UCL_ARRAY, 0);
    if (arr) {
        ucl_array_append(arr, ucl_object_fromstring("elem1"));
        ucl_array_append(arr, ucl_object_fromstring("elem2"));
    }
    return arr;
}

int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create dummy UCL objects
    ucl_object_t *obj = create_dummy_ucl_object();
    ucl_object_t *arr = create_dummy_ucl_array();

    if (!obj || !arr) {
        if (obj) ucl_object_unref(obj);
        if (arr) ucl_object_unref(arr);
        return 0;
    }

    // Prepare a null-terminated string from the input data
    char path[256];
    size_t path_len = (Size < sizeof(path) - 1) ? Size : sizeof(path) - 1;
    memcpy(path, Data, path_len);
    path[path_len] = '\0';

    // Fuzz ucl_object_lookup_path
    const ucl_object_t *result = ucl_object_lookup_path(obj, path);

    // Fuzz ucl_object_replace_key
    ucl_object_t *new_obj = ucl_object_fromstring("new_value");
    if (new_obj) {
        ucl_object_replace_key(obj, new_obj, path, path_len, true);
    }

    // Fuzz ucl_object_delete_key
    ucl_object_delete_key(obj, path);

    // Fuzz ucl_object_reserve
    ucl_object_reserve(arr, path_len);

    // Fuzz ucl_object_merge
    ucl_object_merge(obj, arr, true);

    // Fuzz ucl_object_type
    ucl_type_t type = ucl_object_type(obj);

    // Cleanup
    ucl_object_unref(obj);
    ucl_object_unref(arr);

    return 0;
}