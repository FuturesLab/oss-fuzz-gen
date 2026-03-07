#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t pointers
    ucl_object_t *array_obj = NULL;
    ucl_object_t *element_obj = NULL;

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);

    // Feed the input data to the parser
    if (parser != NULL) {
        ucl_parser_add_chunk(parser, data, size);

        // Get the root object after parsing
        array_obj = ucl_parser_get_object(parser);

        // Assuming the input data can be parsed into a valid UCL object,
        // we create a dummy element object to search for
        element_obj = ucl_object_fromstring("dummy_element");

        if (array_obj != NULL && element_obj != NULL) {
            // Call the function-under-test
            unsigned int index = ucl_array_index_of(array_obj, element_obj);

            // Use the index (e.g., print it, log it, etc.)
            // For this harness, we simply ensure the function is called
        }
    }

    // Clean up
    if (array_obj != NULL) {
        ucl_object_unref(array_obj);
    }
    if (element_obj != NULL) {
        ucl_object_unref(element_obj);
    }
    if (parser != NULL) {
        ucl_parser_free(parser);
    }

    return 0;
}