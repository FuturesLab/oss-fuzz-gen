#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser as a string
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object from the parser
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);

    // Use a key for lookup, ensure it's null-terminated
    const char *key = "example_key";

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup(root_obj, key);

    // Clean up
    if (root_obj != NULL) {
        ucl_object_unref(root_obj);
    }
    ucl_parser_free(parser);

    return 0;
}