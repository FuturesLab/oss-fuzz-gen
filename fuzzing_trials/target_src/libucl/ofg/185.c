#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data as a UCL object
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object from the parser
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Define a sample key and a void pointer for lookup
    const char *key = "sample_key";
    void *user_data = (void *)0x1; // Example non-NULL void pointer

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup_any(root, key, user_data);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}