#include <stdint.h>
#include <stdbool.h>
#include <ucl.h>

// Use the 'struct' keyword for ucl_parser
int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    const ucl_object_t *root_obj = NULL;
    ucl_object_iter_t iter = NULL;
    int error = 0;
    bool expand_values = true;

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);

    // Parse the input data
    if (ucl_parser_add_chunk(parser, data, size)) {
        root_obj = ucl_parser_get_object(parser);

        // Iterate over the parsed object
        const ucl_object_t *result = ucl_object_iterate_with_error(root_obj, &iter, expand_values, &error);

        // Check the result (optional, for debugging purposes)
        if (result == NULL && error != 0) {
            // Handle iteration error if needed
        }
    }

    // Clean up
    if (root_obj != NULL) {
        // Cast away the constness to match the function signature
        ucl_object_unref((ucl_object_t *)root_obj);
    }
    ucl_parser_free(parser);

    return 0;
}