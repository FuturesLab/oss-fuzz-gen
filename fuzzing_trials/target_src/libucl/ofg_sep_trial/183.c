#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Ensure the input is large enough to split into meaningful parts
    if (size < 2) {
        return 0;
    }

    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data as UCL
    ucl_parser_add_chunk(parser, data, size);
    const ucl_object_t *root = ucl_parser_get_object(parser);

    // Prepare a non-null string key
    const char *key = "test_key";

    // Prepare a non-null void pointer
    int dummy_data = 42; // Example integer data
    void *user_data = &dummy_data;

    // Call the function under test
    const ucl_object_t *result = ucl_object_lookup_any(root, key, user_data);

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    }
    ucl_parser_free(parser);

    return 0;
}