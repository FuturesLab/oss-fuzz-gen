#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a meaningful ucl_object_t
    if (size == 0) {
        return 0;
    }

    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a UCL object from the input data
    ucl_object_t *obj = ucl_object_fromstring_common((const char *)data, size, 0);
    if (obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function under test
    bool result = ucl_set_include_path(parser, obj);

    // Clean up
    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}