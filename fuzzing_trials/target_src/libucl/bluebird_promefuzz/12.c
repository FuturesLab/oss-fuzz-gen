#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
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

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
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
    ucl_object_lookup(top, key);

    // Test ucl_object_insert_key_merged
    ucl_object_insert_key_merged(top, merged_elt, key, keylen, copy_key);

    // Test ucl_object_pop_key
    ucl_object_t *popped = ucl_object_pop_key(top, key);
    if (popped && popped != elt && popped != replace_elt && popped != merged_elt) {
        free_ucl_object(popped);
    }

    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_pop_key to ucl_object_pop_keyl
    char *fxokebhg[1024] = {"brnkx", NULL};

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_pop_key to ucl_object_type

    ucl_type_t ret_ucl_object_type_xejct = ucl_object_type(popped);

    // End mutation: Producer.APPEND_MUTATOR

    struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_esvkb = ucl_object_emit_memory_funcs(fxokebhg);
    if (ret_ucl_object_emit_memory_funcs_esvkb == NULL){
    	return 0;
    }
    unsigned int ret_ucl_parser_get_column_vphff = ucl_parser_get_column(NULL);
    if (ret_ucl_parser_get_column_vphff < 0){
    	return 0;
    }

    ucl_object_t* ret_ucl_object_pop_keyl_ixjlu = ucl_object_pop_keyl(popped, (const char *)*fxokebhg, (size_t )ret_ucl_parser_get_column_vphff);
    if (ret_ucl_object_pop_keyl_ixjlu == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(key);
    free_ucl_object(top);
    free_ucl_object(elt);
    free_ucl_object(replace_elt);
    free_ucl_object(merged_elt);

    return 0;
}