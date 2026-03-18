#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_object_t *root = NULL;
    ucl_object_t *new_obj = NULL;
    ucl_object_t *result = NULL;
    unsigned int index = 0;

    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    ucl_parser_add_chunk(parser, data, size);
    root = ucl_parser_get_object(parser);

    // Check if the root object is an array
    if (root != NULL && ucl_object_type(root) == UCL_ARRAY) {
        // Create a new UCL object to replace an existing element
        new_obj = ucl_object_fromstring("new_value");

        // Use a small index for replacement
        index = size % 10;  // Ensure index is within a reasonable range

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