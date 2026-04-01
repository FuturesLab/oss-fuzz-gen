#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    ucl_object_t *obj;
    const char *result_str;
    size_t result_len;
    bool success;

    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the parsed UCL object
    obj = ucl_parser_get_object(parser);
    if (obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    success = ucl_object_tolstring_safe(obj, &result_str, &result_len);

    // Clean up
    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}