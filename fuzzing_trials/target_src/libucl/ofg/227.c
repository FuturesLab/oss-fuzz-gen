#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
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
    ucl_object_t *search_obj = ucl_object_fromstring("test");

    // Call the function-under-test
    unsigned int index = ucl_array_index_of(root, search_obj);

    // Clean up
    ucl_object_unref(search_obj);
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}