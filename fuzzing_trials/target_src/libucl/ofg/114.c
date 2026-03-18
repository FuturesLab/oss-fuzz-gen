#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

// Fuzzing harness for ucl_object_iterate_full
int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    ucl_object_t *root = NULL;
    ucl_object_iter_t iter;
    const ucl_object_t *obj;
    enum ucl_iterate_type iterate_type = UCL_ITERATE_BOTH; // Changed from UCL_ITERATE_OBJECT to UCL_ITERATE_BOTH

    // Parse the input data into a UCL object
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    ucl_parser_add_chunk(parser, data, size);
    root = ucl_parser_get_object(parser);
    ucl_parser_free(parser);

    if (root == NULL) {
        return 0;
    }

    // Initialize the iterator
    iter = ucl_object_iterate_new(root);

    // Call the function under test
    obj = ucl_object_iterate_full(iter, iterate_type);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(root);

    return 0;
}