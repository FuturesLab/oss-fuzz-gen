#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *ucl_obj = NULL;
    const char *result_str = NULL;
    size_t result_len = 0;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the UCL object
    ucl_obj = ucl_parser_get_object(parser);
    ucl_parser_free(parser);
    if (ucl_obj == NULL) {
        return 0;
    }

    // Call the function-under-test
    bool success = ucl_object_tolstring_safe(ucl_obj, &result_str, &result_len);

    // Clean up
    if (ucl_obj != NULL) {
        ucl_object_unref(ucl_obj);
    }

    return 0;
}