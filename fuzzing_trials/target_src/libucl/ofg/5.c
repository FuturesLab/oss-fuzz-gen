#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *obj = ucl_object_new();
    ucl_emitter_t emitter_type = UCL_EMIT_JSON;
    size_t emitted_length = 0;

    // Ensure data is not NULL and size is greater than 0
    if (data == NULL || size == 0) {
        return 0;
    }

    // Parse the input data into a ucl_object_t
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);
    if (parser == NULL) {
        ucl_object_unref(obj);
        return 0;
    }

    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        ucl_object_unref(obj);
        return 0;
    }

    const ucl_object_t *parsed_obj = ucl_parser_get_object(parser);
    if (parsed_obj == NULL) {
        ucl_parser_free(parser);
        ucl_object_unref(obj);
        return 0;
    }

    // Call the function under test
    unsigned char *result = ucl_object_emit_len(parsed_obj, emitter_type, &emitted_length);

    // Free allocated resources
    if (result != NULL) {
        free(result);
    }
    ucl_object_unref((ucl_object_t *)parsed_obj);
    ucl_parser_free(parser);

    return 0;
}