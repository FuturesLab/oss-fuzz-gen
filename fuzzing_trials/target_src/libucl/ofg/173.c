#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object from the parser
    ucl_object_t *root_obj = ucl_parser_get_object(parser);

    // Ensure the root object is not NULL
    if (root_obj != NULL) {
        // Call the function under test
        ucl_object_t *popped_obj = ucl_array_pop_first(root_obj);

        // Free the popped object if it's not NULL
        if (popped_obj != NULL) {
            ucl_object_unref(popped_obj);
        }

        // Free the root object
        ucl_object_unref(root_obj);
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}