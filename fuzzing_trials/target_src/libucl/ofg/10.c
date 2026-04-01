#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    if (!ucl_parser_add_string(parser, (const char *)data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        const char *key = ucl_object_key(obj);
        if (key != NULL) {
            // Use the key for further processing if needed
        }
    }

    ucl_parser_free(parser);
    return 0;
}