#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static ucl_object_t* create_ucl_object(const char* key, const char* value) {
    ucl_object_t* obj = (ucl_object_t*)malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->key = key;
        obj->value.sv = value;
        obj->keylen = key ? strlen(key) : 0;
    }
    return obj;
}

static void free_ucl_object(ucl_object_t* obj) {
    if (obj) {
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char* key1 = "key1";
    const char* key2 = "key2";
    const char* comment1 = "comment1";
    const char* comment2 = "comment2";

    ucl_object_t* obj = create_ucl_object(key1, (const char*)Data);
    ucl_object_t* obj2 = create_ucl_object(key2, (const char*)Data);

    if (obj == NULL || obj2 == NULL) {
        free_ucl_object(obj);
        free_ucl_object(obj2);
        return 0;
    }
    
    const ucl_object_t* found_obj1 = ucl_object_lookup(obj, key1);
    const ucl_object_t* found_obj2 = ucl_object_lookup(obj2, key2);

    ucl_comments_add(obj, found_obj1, comment1);
    ucl_comments_add(obj2, found_obj2, comment2);

    const ucl_object_t* found_comment1 = ucl_comments_find(obj, found_obj1);
    const ucl_object_t* found_comment2 = ucl_comments_find(obj2, found_obj2);

    ucl_comments_move(obj, found_obj1, found_obj2);

    free_ucl_object(obj);
    free_ucl_object(obj2);
    return 0;
}