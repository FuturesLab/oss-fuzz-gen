#include <stdint.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    ucl_object_t *obj = NULL;
    ucl_object_iter_t iter = NULL;

    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object
    obj = ucl_parser_get_object(parser);
    if (obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function under test
    iter = ucl_object_iterate_reset(iter, obj);

    // Clean up
    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}