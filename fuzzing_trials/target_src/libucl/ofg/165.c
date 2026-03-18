#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Ensure size is greater than 0 to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Initialize a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        free(input_str);
        return 0;
    }

    // Parse the input string into a UCL object
    if (!ucl_parser_add_string(parser, input_str, size)) {
        ucl_parser_free(parser);
        free(input_str);
        return 0;
    }

    // Get the root UCL object
    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        // Call the function-under-test
        char *result = ucl_copy_value_trash(obj);

        // Free the result if it is not NULL
        if (result != NULL) {
            free(result);
        }
    }

    // Clean up
    ucl_object_unref(obj);
    ucl_parser_free(parser);
    free(input_str);

    return 0;
}