#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
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
    bool result = ucl_parser_add_string_priority(parser, input_string, size, priority);

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
        int ret_ucl_parser_get_error_code_omogi = ucl_parser_get_error_code(parser);
        if (ret_ucl_parser_get_error_code_omogi < 0){
        	return 0;
        }

        ucl_object_t* ret_ucl_parser_get_current_stack_object_gzfbm = ucl_parser_get_current_stack_object(parser, (unsigned int )ret_ucl_parser_get_error_code_omogi);
        if (ret_ucl_parser_get_current_stack_object_gzfbm == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_file_priority
        const ucl_object_t fhujwyyd;
        memset(&fhujwyyd, 0, sizeof(fhujwyyd));
        char* ret_ucl_copy_value_trash_omybz = ucl_copy_value_trash(&fhujwyyd);
        if (ret_ucl_copy_value_trash_omybz == NULL){
        	return 0;
        }
        const ucl_object_t bbjmxxhs;
        memset(&bbjmxxhs, 0, sizeof(bbjmxxhs));
        unsigned int ret_ucl_array_size_mvchk = ucl_array_size(&bbjmxxhs);
        if (ret_ucl_array_size_mvchk < 0){
        	return 0;
        }

        bool ret_ucl_parser_add_file_priority_kjjhj = ucl_parser_add_file_priority(parser, ret_ucl_copy_value_trash_omybz, ret_ucl_array_size_mvchk);
        if (ret_ucl_parser_add_file_priority_kjjhj == 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    ucl_parser_free(parser);

    return 0;
}