#include <stdint.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_iter_t iter = NULL;
    bool expand_values = true; // or false, try both variations

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Feed the input data to the parser
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the top-level object
    const ucl_object_t *top_obj = ucl_parser_get_object(parser);
    if (top_obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Initialize the iterator
    iter = ucl_object_iterate_new(top_obj);
    if (iter == NULL) {
        ucl_object_unref(top_obj);
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_iterate_safe(iter, expand_values);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(top_obj);
    ucl_parser_free(parser);

    return 0;
}