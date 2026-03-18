#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

// Fuzzing harness for the function ucl_array_find_index
int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a UCL object from the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root UCL object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Define an index to search for
    unsigned int index = 0; // Start with index 0

    // Call the function-under-test
    const ucl_object_t *result = ucl_array_find_index(root, index);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}