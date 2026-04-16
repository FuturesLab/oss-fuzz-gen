#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include "ucl.h"

static ucl_object_t *create_random_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        memset(obj, 0, sizeof(ucl_object_t));
        obj->type = UCL_OBJECT;
    }
    return obj;
}

static void free_ucl_object(ucl_object_t *obj) {
    if (obj) {
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare dummy UCL objects
    ucl_object_t *top = create_random_ucl_object();
    ucl_object_t *elt = create_random_ucl_object();
    ucl_object_t *replace_elt = create_random_ucl_object();
    ucl_object_t *merged_elt = create_random_ucl_object();

    if (!top || !elt || !replace_elt || !merged_elt) {
        free_ucl_object(top);
        free_ucl_object(elt);
        free_ucl_object(replace_elt);
        free_ucl_object(merged_elt);
        return 0;
    }

    // Prepare a key
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        free_ucl_object(top);
        free_ucl_object(elt);
        free_ucl_object(replace_elt);
        free_ucl_object(merged_elt);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0'; // Ensure null-termination
    size_t keylen = Size;
    bool copy_key = Data[0] % 2 == 0;

    // Test ucl_object_insert_key
    ucl_object_insert_key(top, elt, key, keylen, copy_key);

    // Test ucl_object_replace_key
    ucl_object_replace_key(top, replace_elt, key, keylen, copy_key);

    // Test ucl_object_delete_key
    ucl_object_delete_key(top, key);

    // Test ucl_object_lookup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_delete_key to ucl_array_delete

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_delete_key to ucl_object_insert_key_merged
    ucl_object_t* ret_ucl_object_fromstring_fnesx = ucl_object_fromstring((const char *)"w");
    if (ret_ucl_object_fromstring_fnesx == NULL){
    	return 0;
    }
    bool ret_ucl_object_insert_key_merged_wobla = ucl_object_insert_key_merged(top, ret_ucl_object_fromstring_fnesx, (const char *)Data, Size, 1);
    if (ret_ucl_object_insert_key_merged_wobla == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_t* ret_ucl_object_fromint_hlbif = ucl_object_fromint(-1);
    if (ret_ucl_object_fromint_hlbif == NULL){
    	return 0;
    }
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ucl_array_delete with ucl_elt_append
    ucl_object_t* ret_ucl_array_delete_mrych = ucl_elt_append(ret_ucl_object_fromint_hlbif, top);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR
    if (ret_ucl_array_delete_mrych == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_lookup(top, key);

    // Test ucl_object_insert_key_merged
    ucl_object_insert_key_merged(top, merged_elt, key, keylen, copy_key);

    // Test ucl_object_pop_key
    ucl_object_t *popped = ucl_object_pop_key(top, key);
    if (popped && popped != elt && popped != replace_elt && popped != merged_elt) {
        free_ucl_object(popped);
    }

    // Cleanup
    free(key);
    free_ucl_object(top);
    free_ucl_object(elt);
    free_ucl_object(replace_elt);
    free_ucl_object(merged_elt);

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

    LLVMFuzzerTestOneInput_5(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
