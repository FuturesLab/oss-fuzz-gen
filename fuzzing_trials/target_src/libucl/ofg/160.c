#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);

    // Parse the input data as UCL object
    if (parser != NULL && size > 0) {
        ucl_parser_add_chunk(parser, data, size);
        const ucl_object_t *root = ucl_parser_get_object(parser);

        if (root != NULL) {
            // Define a non-NULL path and key character
            const char *path = "example.path";
            const char key = '.';

            // Call the function-under-test
            const ucl_object_t *result = ucl_object_lookup_path_char(root, path, key);

            // Optionally, perform some operations with `result`
            if (result != NULL) {
                // Example operation: retrieve and print the type of the result
                ucl_type_t type = ucl_object_type(result);
                (void)type; // Suppress unused variable warning
            }

            // Free the UCL object
            ucl_object_unref(root);
        }

        // Clean up parser
        ucl_parser_free(parser);
    }

    return 0;
}