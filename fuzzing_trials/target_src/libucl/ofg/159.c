#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Initialize ucl_parser
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

    // Use a fixed index for fuzzing
    unsigned int index = size % 10; // Example fixed index based on size

    // Call the function-under-test
    const ucl_object_t *result = ucl_array_find_index(root, index);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}