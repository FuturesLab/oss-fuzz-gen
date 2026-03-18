#include <stdint.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    if (size < sizeof(ucl_object_iter_t)) {
        return 0;
    }

    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (!parser) {
        return 0;
    }

    // Feed data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (!root) {
        ucl_parser_free(parser);
        return 0;
    }

    // Create an iterator
    ucl_object_iter_t iter = ucl_object_iterate_new(root);

    // Call the function-under-test with both true and false for the boolean parameter
    const ucl_object_t *obj1 = ucl_object_iterate_safe(iter, true);
    const ucl_object_t *obj2 = ucl_object_iterate_safe(iter, false);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}