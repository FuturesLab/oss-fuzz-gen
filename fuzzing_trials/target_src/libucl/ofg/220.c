#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data as UCL
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Define a key to lookup
    const char *key = "test_key";
    size_t key_len = 8; // Length of "test_key"

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup_len(root, key, key_len);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}