#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for our needs
    if (size < 3) {
        return 0;
    }

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data as a UCL object
    ucl_parser_add_chunk(parser, data, size);
    const ucl_object_t *root = ucl_parser_get_object(parser);

    // Prepare a non-NULL path string and separator
    const char *path = "example.path";
    const char separator = '.';

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup_path_char(root, path, separator);

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    }
    ucl_parser_free(parser);

    return 0;
}