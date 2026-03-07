// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_comments_find at ucl_util.c:3925:1 in ucl.h
// ucl_comments_find at ucl_util.c:3925:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_fromstring at ucl_util.c:3078:1 in ucl.h
// ucl_elt_append at ucl_util.c:3397:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ucl.h"

static ucl_object_t* create_dummy_ucl_object() {
    ucl_object_t* obj = ucl_object_typed_new(UCL_OBJECT);
    if (obj) {
        obj->key = "dummy_key";
        obj->keylen = strlen(obj->key);
    }
    return obj;
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    // Create dummy objects for comments and search
    ucl_object_t *comments = create_dummy_ucl_object();
    ucl_object_t *srch = create_dummy_ucl_object();

    // Call `ucl_comments_find` twice with dummy objects
    const ucl_object_t *comment1 = ucl_comments_find(comments, srch);
    const ucl_object_t *comment2 = ucl_comments_find(comments, srch);

    // Create a new UCL object of type UCL_STRING
    ucl_object_t *new_obj = ucl_object_typed_new(UCL_STRING);

    // Use Data to create a string object
    char *str = NULL;
    if (Size > 0) {
        str = (char *)malloc(Size + 1);
        if (str) {
            memcpy(str, Data, Size);
            str[Size] = '\0';
        }
    }

    // Create UCL object from string
    ucl_object_t *str_obj = NULL;
    if (str) {
        str_obj = ucl_object_fromstring(str);
    }

    // Append the string object to the new object only if str_obj is not NULL
    ucl_object_t *result = new_obj;
    if (str_obj) {
        result = ucl_elt_append(new_obj, str_obj);
    }

    // Cleanup
    if (comments) ucl_object_unref(comments);
    if (srch) ucl_object_unref(srch);
    // Avoid double-freeing str_obj by not unref'ing it if it was appended
    if (str_obj && str_obj != result) ucl_object_unref(str_obj);
    if (new_obj && new_obj != result) ucl_object_unref(new_obj);
    if (str) free(str);

    return 0;
}