#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Initialize a ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);

    // Parse the input data
    if (parser != NULL && ucl_parser_add_chunk(parser, data, size)) {
        // Get the root object
        const ucl_object_t *root = ucl_parser_get_object(parser);

        // Ensure the root object is not NULL
        if (root != NULL) {
            // Create a path string from the input data
            char path[256];
            size_t path_len = size < 255 ? size : 255;
            memcpy(path, data, path_len);
            path[path_len] = '\0';

            // Call the function-under-test
            const ucl_object_t *result = ucl_object_lookup_path(root, path);

            // Optionally, you can do something with the result here
            (void)result; // Suppress unused variable warning
        }

        // Free the root object
        ucl_object_unref(root);
    }

    // Clean up the parser
    ucl_parser_free(parser);

    return 0;
}