#include <ucl.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data as a string to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object from the parser
    const ucl_object_t *root = ucl_parser_get_object(parser);

    if (root != NULL) {
        // Call the function under test
        const ucl_object_t *head = ucl_array_head(root);

        // Do something with the result to prevent compiler optimizations
        if (head != NULL) {
            // Dummy operation
            (void)ucl_object_tostring(head);
        }
    }

    // Free the parser and the root object
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}