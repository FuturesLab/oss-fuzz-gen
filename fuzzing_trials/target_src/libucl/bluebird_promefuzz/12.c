#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include "ucl.h"

static ucl_object_t* create_random_ucl_object() {
    ucl_object_t *obj = malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->value.ov = NULL; // Initialize to NULL or a valid object structure
        obj->key = NULL;
        obj->next = NULL;
        obj->prev = NULL;
        obj->keylen = 0;
        obj->len = 0;
        obj->ref = 1; // Initialize reference count
        obj->flags = 0;
        obj->type = 0;
        obj->trash_stack[0] = NULL;
        obj->trash_stack[1] = NULL;
    }
    return obj;
}

static void cleanup_ucl_object(ucl_object_t *obj) {
    if (obj) {
        if (obj->key) {
            free((void*)obj->key);
        }
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ucl_object_t *top = create_random_ucl_object();
    ucl_object_t *elt = create_random_ucl_object();
    if (!top || !elt) {
        cleanup_ucl_object(top);
        cleanup_ucl_object(elt);
        return 0;
    }

    // Ensure the key is null-terminated to avoid buffer overflow
    char *key = malloc(Size + 1);
    if (!key) {
        cleanup_ucl_object(top);
        cleanup_ucl_object(elt);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';
    size_t keylen = Size;
    bool copy_key = true;

    // Test ucl_object_replace_key
    ucl_object_replace_key(top, elt, key, keylen, copy_key);

    // Test ucl_object_delete_keyl
    ucl_object_delete_keyl(top, key, keylen);

    // Test ucl_object_keyl
    size_t len;
    const char *retrieved_key = ucl_object_keyl(top, &len);

    // Test ucl_object_pop_key

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_keyl to ucl_object_tolstring
    ucl_object_t* ret_ucl_object_frombool_ycpox = ucl_object_frombool(0);
    if (ret_ucl_object_frombool_ycpox == NULL){
    	return 0;
    }
    const char* ret_ucl_object_tolstring_zenzo = ucl_object_tolstring(ret_ucl_object_frombool_ycpox, &len);
    if (ret_ucl_object_tolstring_zenzo == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_t *popped_obj = ucl_object_pop_key(top, key);
    cleanup_ucl_object(popped_obj);

    // Test ucl_object_lookup_len
    const ucl_object_t *looked_up_obj = ucl_object_lookup_len(top, key, keylen);

    // Test ucl_object_pop_keyl
    ucl_object_t *popped_obj_l = ucl_object_pop_keyl(top, key, keylen);
    cleanup_ucl_object(popped_obj_l);

    cleanup_ucl_object(top);
    free(key);
    // Do not cleanup `elt` here as it may have been freed by libucl functions

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_12(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
