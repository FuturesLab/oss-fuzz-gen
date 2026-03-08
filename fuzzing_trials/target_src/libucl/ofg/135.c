#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data to create a UCL object
    ucl_object_t *root = NULL;
    ucl_parser_add_chunk(parser, data, size);
    root = ucl_parser_get_object(parser);
    ucl_parser_free(parser);

    // Check if the root object is valid
    if (root == NULL) {
        return 0;
    }

    // Create a new UCL object to replace in the array
    ucl_object_t *new_obj = ucl_object_fromstring("replacement");

    // Extract an unsigned int from the data to use as the index
    unsigned int index = *(unsigned int *)(data + size - sizeof(unsigned int));

    // Call the function under test
    ucl_object_t *result = ucl_array_replace_index(root, new_obj, index);

    // Clean up
    ucl_object_unref(root);
    ucl_object_unref(new_obj);

    // If result is not NULL, unref it
    if (result != NULL) {
        ucl_object_unref(result);
    }

    return 0;
}