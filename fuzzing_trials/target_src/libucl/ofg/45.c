#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    ucl_parser_add_string(parser, (const char *)data, size);
    if (ucl_parser_get_error(parser) != NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        size_t len = 0;
        const char *str = ucl_object_tolstring(obj, &len);
        if (str != NULL) {
            printf("Converted string: %s\n", str);
            printf("String length: %zu\n", len);
        }
    }

    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}