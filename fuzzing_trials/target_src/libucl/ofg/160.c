#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Ensure the root object is an array
    if (ucl_object_type(root) != UCL_ARRAY) {
        ucl_object_unref(root);
        ucl_parser_free(parser);
        return 0;
    }

    // Create a non-NULL index to search for
    unsigned int index = 1; // Example index, should be varied for thorough testing

    // Call the function-under-test
    const ucl_object_t *result = ucl_array_find_index(root, index);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}