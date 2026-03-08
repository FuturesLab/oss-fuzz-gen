#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    ucl_object_t *copy_obj = ucl_object_copy(obj);
    if (copy_obj != NULL) {
        ucl_object_unref(copy_obj);
    }

    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}