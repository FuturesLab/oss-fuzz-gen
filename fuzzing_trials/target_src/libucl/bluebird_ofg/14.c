#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);

    // Call the function-under-test if root is not NULL
    if (root != NULL) {
        ucl_type_t type = ucl_object_type(root);
    }

    // Free the parser and the root object
    ucl_object_unref(root);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_unref to ucl_array_prepend
    ucl_object_t* ret_ucl_parser_get_object_qgruy = ucl_parser_get_object(parser);
    if (ret_ucl_parser_get_object_qgruy == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_object to ucl_array_find_index
    unsigned int ret_ucl_parser_get_linenum_hxdyc = ucl_parser_get_linenum(NULL);
    if (ret_ucl_parser_get_linenum_hxdyc < 0){
    	return 0;
    }

    const ucl_object_t* ret_ucl_array_find_index_yjuox = ucl_array_find_index(root, ret_ucl_parser_get_linenum_hxdyc);
    if (ret_ucl_array_find_index_yjuox == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bool ret_ucl_array_prepend_zocff = ucl_array_prepend(root, ret_ucl_parser_get_object_qgruy);
    if (ret_ucl_array_prepend_zocff == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ucl_parser_free(parser);

    return 0;
}