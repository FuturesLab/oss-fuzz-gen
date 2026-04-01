#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Initialize ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a UCL object from the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    const ucl_object_t *ucl_obj = ucl_parser_get_object(parser);
    if (ucl_obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Define a non-NULL path and delimiter for testing
    const char *path = "test.path";
    char delimiter = '.';

    // Call the function under test
    const ucl_object_t *result = ucl_object_lookup_path_char(ucl_obj, path, delimiter);

    // Clean up
    ucl_object_unref(ucl_obj);
    ucl_parser_free(parser);

    return 0;
}