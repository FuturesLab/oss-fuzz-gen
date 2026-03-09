#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Initialize a ucl_object_t
    ucl_object_t *obj = ucl_object_new();

    // Ensure the data is not NULL and size is greater than zero
    if (data != NULL && size > 0) {
        // Create a UCL parser
        struct ucl_parser *parser = ucl_parser_new(0);

        // Parse the input data
        if (ucl_parser_add_chunk(parser, data, size)) {
            // Get the UCL object from the parser
            const ucl_object_t *top = ucl_parser_get_object(parser);

            // Define a ucl_emitter, using a valid enum value
            enum ucl_emitter emitter_type = UCL_EMIT_JSON;

            // Call the function-under-test
            unsigned char *result = ucl_object_emit(top, emitter_type);

            // Free the result if not NULL
            if (result != NULL) {
                free(result);
            }

            // Decrement the reference count of the UCL object
            ucl_object_unref(top);
        }

        // Clean up the parser
        ucl_parser_free(parser);
    }

    // Free the UCL object
    ucl_object_unref(obj);

    return 0;
}