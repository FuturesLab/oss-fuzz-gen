#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
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

    // Get the parsed UCL object
    const ucl_object_t *ucl_obj = ucl_parser_get_object(parser);
    if (ucl_obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Define an emitter type, using a valid enumeration value
    enum ucl_emitter emitter_type = UCL_EMIT_JSON;

    // Call the function-under-test
    unsigned char *result = ucl_object_emit(ucl_obj, emitter_type);

    // Free the result if it was allocated
    if (result != NULL) {
        free(result);
    }

    // Clean up
    ucl_object_unref(ucl_obj);
    ucl_parser_free(parser);

    return 0;
}