#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *ucl_obj = NULL;
    ucl_emitter_t emitter_type = UCL_EMIT_JSON; // Corrected type name

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
    if (ucl_obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    unsigned char *result = ucl_object_emit(ucl_obj, emitter_type);

    // Free allocated resources
    if (result != NULL) {
        free(result);
    }
    ucl_object_unref(ucl_obj);
    ucl_parser_free(parser);

    return 0;
}