#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *obj = ucl_object_new();
    ucl_emitter_t emitter = UCL_EMIT_JSON_COMPACT;
    unsigned char *result;

    // Ensure the data is not empty
    if (size > 0) {
        // Create a UCL parser
        struct ucl_parser *parser = ucl_parser_new(0);

        // Feed data to the parser
        if (ucl_parser_add_chunk(parser, data, size)) {
            // Get the UCL object
            obj = ucl_parser_get_object(parser);
        }

        // Free the parser
        ucl_parser_free(parser);
    }

    // Call the function-under-test
    result = ucl_object_emit(obj, emitter);

    // Clean up
    if (result != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}