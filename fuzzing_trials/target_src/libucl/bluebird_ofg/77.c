#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_set_include_path to ucl_parser_add_file_full
    const ucl_object_t kmsyvbhl;
    memset(&kmsyvbhl, 0, sizeof(kmsyvbhl));
    char* ret_ucl_copy_value_trash_rgjvy = ucl_copy_value_trash(&kmsyvbhl);
    if (ret_ucl_copy_value_trash_rgjvy == NULL){
    	return 0;
    }

    bool ret_ucl_parser_add_file_full_gtsqh = ucl_parser_add_file_full(parser, ret_ucl_copy_value_trash_rgjvy, 64, 0, 0);
    if (ret_ucl_parser_add_file_full_gtsqh == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(input_string);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_get_current_stack_object
        int ret_ucl_parser_get_default_priority_toqmx = ucl_parser_get_default_priority(parser);
        if (ret_ucl_parser_get_default_priority_toqmx < 0){
        	return 0;
        }

        ucl_object_t* ret_ucl_parser_get_current_stack_object_nmsuz = ucl_parser_get_current_stack_object(parser, (unsigned int )ret_ucl_parser_get_default_priority_toqmx);
        if (ret_ucl_parser_get_current_stack_object_nmsuz == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    ucl_parser_free(parser);

    return 0;
}