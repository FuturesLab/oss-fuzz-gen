// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_strdup_impl at ucl.h:80:21 in ucl.h
// ucl_object_keyl at ucl_util.c:3581:1 in ucl.h
// ucl_object_replace_key at ucl_util.c:2545:6 in ucl.h
// ucl_copy_key_trash at ucl_util.c:494:1 in ucl.h
// ucl_object_key at ucl_util.c:3575:1 in ucl.h
// ucl_object_pop_keyl at ucl_util.c:2509:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure the input data is null-terminated
    char *input_data = (char *)malloc(Size + 1);
    if (!input_data) return 0;
    memcpy(input_data, Data, Size);
    input_data[Size] = '\0';

    // Test ucl_strdup_impl
    char *str = ucl_strdup_impl(input_data);
    if (str != NULL) {
        free(str);
    }

    // Prepare a dummy UCL object
    ucl_object_t obj;
    obj.key = input_data;
    obj.keylen = Size > UINT32_MAX ? UINT32_MAX : (uint32_t)Size;
    obj.ref = 1;

    // Test ucl_object_keyl
    size_t len;
    const char *key = ucl_object_keyl(&obj, &len);
    if (key != NULL) {
        // Do something with the key
    }

    // Test ucl_object_replace_key
    ucl_object_t top;
    top.type = UCL_OBJECT;
    ucl_object_t elt;
    bool replaced = ucl_object_replace_key(&top, &elt, input_data, Size, true);

    // Test ucl_copy_key_trash
    char *copied_key = ucl_copy_key_trash(&obj);
    if (copied_key != NULL) {
        // Do something with the copied key
    }

    // Test ucl_object_key
    const char *null_terminated_key = ucl_object_key(&obj);
    if (null_terminated_key != NULL) {
        // Do something with the null-terminated key
    }

    // Test ucl_object_pop_keyl
    ucl_object_t *popped_obj = ucl_object_pop_keyl(&top, input_data, Size);
    if (popped_obj != NULL) {
        // Do something with the popped object
    }

    // Free the allocated input data
    free(input_data);

    return 0;
}