#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_object_t *root = NULL;
    ucl_object_t *new_obj = NULL;
    unsigned int index = 0;

    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    root = ucl_parser_get_object(parser);

    // Create a new UCL object to replace
    new_obj = ucl_object_fromstring("replacement");

    // Ensure root is not NULL and is an array
    if (root != NULL && ucl_object_type(root) == UCL_ARRAY) {
        // Call the function-under-test
        ucl_object_t *result = ucl_array_replace_index(root, new_obj, index);

        // Clean up the result if it's not the same as new_obj
        if (result != new_obj) {
            ucl_object_unref(result);
        }
    }

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    }
    ucl_object_unref(new_obj);
    ucl_parser_free(parser);

    return 0;
}