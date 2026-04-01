#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

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
        unsigned int array_size = ucl_array_size(obj);
        (void)array_size; // Use the result to avoid unused variable warning
    }

    ucl_parser_free(parser);

    return 0;
}