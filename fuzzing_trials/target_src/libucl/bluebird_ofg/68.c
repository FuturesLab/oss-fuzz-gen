#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    char *input_string;
    unsigned int priority;

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    if (parser == NULL) {
        return 0;
    }

    // Ensure that the input string is null-terminated
    input_string = (char *)malloc(size + 1);
    if (input_string == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Set a fixed priority for fuzzing
    priority = 1;

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of ucl_parser_add_string_priority
    bool result = ucl_parser_add_string_priority(parser, input_string, 0, priority);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_string_priority to ucl_set_include_path
    ucl_object_t* ret_ucl_object_fromint_jmawh = ucl_object_fromint(64);
    if (ret_ucl_object_fromint_jmawh == NULL){
    	return 0;
    }

    bool ret_ucl_set_include_path_emufb = ucl_set_include_path(parser, ret_ucl_object_fromint_jmawh);
    if (ret_ucl_set_include_path_emufb == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(input_string);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_get_current_stack_object
        const ucl_object_t tmaaujbb;
        memset(&tmaaujbb, 0, sizeof(tmaaujbb));
        double ret_ucl_object_todouble_lmtfo = ucl_object_todouble(&tmaaujbb);
        if (ret_ucl_object_todouble_lmtfo < 0){
        	return 0;
        }

        ucl_object_t* ret_ucl_parser_get_current_stack_object_iebfm = ucl_parser_get_current_stack_object(parser, (unsigned int )ret_ucl_object_todouble_lmtfo);
        if (ret_ucl_parser_get_current_stack_object_iebfm == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_current_stack_object to ucl_object_insert_key
        ucl_object_t* ret_ucl_parser_get_object_vcpsu = ucl_parser_get_object(NULL);
        if (ret_ucl_parser_get_object_vcpsu == NULL){
        	return 0;
        }
        char* ret_ucl_copy_key_trash_zpecr = ucl_copy_key_trash(ret_ucl_object_fromint_jmawh);
        if (ret_ucl_copy_key_trash_zpecr == NULL){
        	return 0;
        }
        int ret_ucl_parser_get_error_code_khahu = ucl_parser_get_error_code(parser);
        if (ret_ucl_parser_get_error_code_khahu < 0){
        	return 0;
        }
        bool ret_ucl_object_iter_chk_excpn_ohuei = ucl_object_iter_chk_excpn(NULL);
        if (ret_ucl_object_iter_chk_excpn_ohuei == 0){
        	return 0;
        }

        bool ret_ucl_object_insert_key_owhoc = ucl_object_insert_key(ret_ucl_parser_get_current_stack_object_iebfm, ret_ucl_parser_get_object_vcpsu, ret_ucl_copy_key_trash_zpecr, (size_t )ret_ucl_parser_get_error_code_khahu, ret_ucl_object_iter_chk_excpn_ohuei);
        if (ret_ucl_object_insert_key_owhoc == 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    ucl_parser_free(parser);

    return 0;
}