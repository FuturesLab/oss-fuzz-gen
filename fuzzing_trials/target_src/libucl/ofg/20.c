#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for safe string operations
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data
    if (!ucl_parser_add_string(parser, input, size)) {
        free(input);
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root UCL object
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);
    if (root_obj != NULL) {
        // Call the function-under-test
        char *key_copy = ucl_copy_key_trash(root_obj);

        // Free the copied key if it was successfully created
        if (key_copy != NULL) {
            free(key_copy);
        }
    }

    // Clean up
    free(input);
    ucl_object_unref(root_obj);
    ucl_parser_free(parser);

    return 0;
}