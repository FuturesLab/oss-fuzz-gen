#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

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

    // Get the root object
    ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Create an iterator
    ucl_object_iter_t iter = ucl_object_iterate_new(root);

    // Choose a valid iterate type
    enum ucl_iterate_type iterate_type = UCL_ITERATE_BOTH;

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_iterate_full(iter, iterate_type);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}

#ifdef __cplusplus
}
#endif