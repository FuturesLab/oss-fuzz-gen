#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_object_t *root = NULL;
    ucl_object_t *new_obj = NULL;
    ucl_object_t *result = NULL;
    unsigned int index = 0;

    // Check if the size is sufficient to parse
    if (size > 0) {
        // Parse the input data
        if (ucl_parser_add_chunk(parser, data, size)) {
            root = ucl_parser_get_object(parser);
        }

        // Create a new UCL object to replace
        new_obj = ucl_object_fromstring("new_value");

        // Use the first byte of data as an index if size allows
        if (size > 1) {
            index = data[0] % 10; // Limit index for simplicity
        }

        // Call the function-under-test
        result = ucl_array_replace_index(root, new_obj, index);

        // Clean up the result if not NULL
        if (result != NULL) {
            ucl_object_unref(result);
        }
    }

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    }
    if (new_obj != NULL) {
        ucl_object_unref(new_obj);
    }
    ucl_parser_free(parser);

    return 0;
}