#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    ucl_parser_add_string(parser, (const char *)data, size);

    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        // Call the function-under-test
        unsigned int array_size = ucl_array_size(obj);

        // Use the result to avoid compiler optimizations removing the call
        if (array_size > 0) {
            // Do something trivial with the result to ensure it's used
            array_size = array_size % 10;
        }
    }

    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}