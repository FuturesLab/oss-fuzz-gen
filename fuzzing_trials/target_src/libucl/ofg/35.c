#include <stdint.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    const ucl_object_t *ucl_obj = NULL;
    ucl_object_iter_t iter = NULL;

    // Parse the input data
    if (parser != NULL && size > 0) {
        ucl_parser_add_chunk(parser, data, size);
        ucl_obj = ucl_parser_get_object(parser);
    }

    // Call the function-under-test
    iter = ucl_object_iterate_reset(iter, ucl_obj);

    // Cleanup
    if (ucl_obj != NULL) {
        ucl_object_unref(ucl_obj);
    }
    if (parser != NULL) {
        ucl_parser_free(parser);
    }

    return 0;
}