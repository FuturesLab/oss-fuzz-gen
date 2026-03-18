#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root != NULL) {
        const char *output_str = NULL;
        size_t output_len = 0;

        // Call the function under test
        bool result = ucl_object_tolstring_safe(root, &output_str, &output_len);

        // Use the result to avoid unused variable warnings
        (void)result;
        (void)output_str;
        (void)output_len;
    }

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}