#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Create a new UCL parser

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
    struct ucl_parser *parser = ucl_parser_new(-1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    ucl_parser_add_chunk(parser, data, size);

    // Get the root UCL object
    ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Create a dummy object to search for in the array

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_object to ucl_elt_append
    ucl_object_t* ret_ucl_object_fromstring_nariy = ucl_object_fromstring((const char *)"r");
    if (ret_ucl_object_fromstring_nariy == NULL){
    	return 0;
    }

    ucl_object_t* ret_ucl_elt_append_cgzkv = ucl_elt_append(root, ret_ucl_object_fromstring_nariy);
    if (ret_ucl_elt_append_cgzkv == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ucl_object_t *search_obj = ucl_object_fromstring("test");

    // Call the function-under-test
    unsigned int index = ucl_array_index_of(root, search_obj);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_array_index_of to ucl_object_replace_key
    ucl_object_t* ret_ucl_array_pop_last_wlzgj = ucl_array_pop_last(root);
    if (ret_ucl_array_pop_last_wlzgj == NULL){
    	return 0;
    }
    ucl_object_t* ret_ucl_array_pop_first_uhwxt = ucl_array_pop_first(root);
    if (ret_ucl_array_pop_first_uhwxt == NULL){
    	return 0;
    }
    struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_wxmuy = ucl_object_emit_memory_funcs((void **)&parser);
    if (ret_ucl_object_emit_memory_funcs_wxmuy == NULL){
    	return 0;
    }
    bool ret_ucl_parser_chunk_skip_sqzsm = ucl_parser_chunk_skip(NULL);
    if (ret_ucl_parser_chunk_skip_sqzsm == 0){
    	return 0;
    }

    bool ret_ucl_object_replace_key_iwpam = ucl_object_replace_key(ret_ucl_array_pop_last_wlzgj, root, &parser, (size_t )index, ret_ucl_parser_chunk_skip_sqzsm);
    if (ret_ucl_object_replace_key_iwpam == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ucl_object_unref(search_obj);
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}