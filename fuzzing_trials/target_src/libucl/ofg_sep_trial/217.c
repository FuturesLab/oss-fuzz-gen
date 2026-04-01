#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for a meaningful test
    if (size < 2) return 0;

    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) return 0;

    // Parse the input data as UCL
    ucl_parser_add_chunk(parser, data, size);
    const ucl_object_t *root = ucl_parser_get_object(parser);

    // Prepare a key for lookup
    const char *key = "test_key";
    size_t key_len = strlen(key);

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup_len(root, key, key_len);

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    }
    ucl_parser_free(parser);

    return 0;
}