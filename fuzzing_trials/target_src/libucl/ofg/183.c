#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    ucl_object_t *obj;

    // Initialize a new UCL parser
    parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);

    // If size is 0, there's nothing to parse
    if (size == 0) {
        ucl_parser_free(parser);
        return 0;
    }

    // Add data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the parsed object
    obj = ucl_parser_get_object(parser);

    // Free the parser
    ucl_parser_free(parser);

    // If the object is not NULL, unref it
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}