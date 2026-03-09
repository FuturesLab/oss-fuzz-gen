#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_string_priority to ucl_object_merge
    const ucl_object_t drtjhybg;
    memset(&drtjhybg, 0, sizeof(drtjhybg));
    ucl_object_t* ret_ucl_object_copy_kyksk = ucl_object_copy(&drtjhybg);
    if (ret_ucl_object_copy_kyksk == NULL){
    	return 0;
    }
    ucl_object_t* ret_ucl_object_fromint_pokpq = ucl_object_fromint(UCL_PRIORITY_MIN);
    if (ret_ucl_object_fromint_pokpq == NULL){
    	return 0;
    }

    bool ret_ucl_object_merge_ekdva = ucl_object_merge(ret_ucl_object_copy_kyksk, ret_ucl_object_fromint_pokpq, result);
    if (ret_ucl_object_merge_ekdva == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

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
        ucl_object_t* ret_ucl_object_fromdouble_vdpco = ucl_object_fromdouble(UCL_PRIORITY_MAX);
        if (ret_ucl_object_fromdouble_vdpco == NULL){
        	return 0;
        }
        unsigned int ret_ucl_parser_get_column_pcbmy = ucl_parser_get_column(parser);
        if (ret_ucl_parser_get_column_pcbmy < 0){
        	return 0;
        }
        bool ret_ucl_object_toboolean_crybx = ucl_object_toboolean(NULL);
        if (ret_ucl_object_toboolean_crybx == 0){
        	return 0;
        }

        bool ret_ucl_object_insert_key_cshii = ucl_object_insert_key(ret_ucl_object_fromdouble_vdpco, ret_ucl_parser_get_current_stack_object_iebfm, (const char *)"w", (size_t )ret_ucl_parser_get_column_pcbmy, ret_ucl_object_toboolean_crybx);
        if (ret_ucl_object_insert_key_cshii == 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    ucl_parser_free(parser);

    return 0;
}