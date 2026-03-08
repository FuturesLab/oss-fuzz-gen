#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    // Step 1: Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0; // Handle memory allocation failure
    }

    // Ensure the input data is null-terminated
    char *input_data = (char *)malloc(Size + 1);
    if (input_data == NULL) {
        ucl_parser_free(parser);
        return 0; // Handle memory allocation failure
    }
    memcpy(input_data, Data, Size);
    input_data[Size] = '\0';

    // Step 2: Add string data to the parser
    bool res = ucl_parser_add_string(parser, input_data, Size);

    // Step 3: Retrieve and print error if any

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_string to ucl_parser_register_macro
    ucl_object_t* ret_ucl_parser_get_object_tfkth = ucl_parser_get_object(parser);
    if (ret_ucl_parser_get_object_tfkth == NULL){
    	return 0;
    }

    bool ret_ucl_parser_register_macro_dxwip = ucl_parser_register_macro(parser, (const char *)Data, NULL, (void *)parser);
    if (ret_ucl_parser_register_macro_dxwip == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    const char *error = ucl_parser_get_error(parser);
    if (error != NULL) {
        // Handle error (in fuzzing context, just continue)
    }

    // Step 4: Attempt to get the top-level UCL object
    ucl_object_t *top_obj = ucl_parser_get_object(parser);

    // Step 5: Free the parser
    ucl_parser_free(parser);

    // Step 6: Iterate over the UCL object if it exists
    if (top_obj != NULL) {
        ucl_object_iter_t it = NULL;
        int ep = 0;
        const ucl_object_t *cur;

        while ((cur = ucl_object_iterate_with_error(top_obj, &it, true, &ep)) != NULL) {
            // Iterate over the object (in fuzzing context, just continue)
        }

        // Step 7: Unref the top-level object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_iterate_with_error to ucl_object_fromstring_common

        ucl_object_t* ret_ucl_object_fromstring_common_rnvgc = ucl_object_fromstring_common((const char *)Data, (size_t )ep, 0);
        if (ret_ucl_object_fromstring_common_rnvgc == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        ucl_object_unref(top_obj);
    }

    // Free the allocated input data
    free(input_data);

    return 0;
}