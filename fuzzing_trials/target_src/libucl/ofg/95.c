#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // If size is 0 we need a null-terminated string.
    // We don't null-terminate the string and by the design
    // of the API passing 0 as size with non null-terminated string
    // gives undefined behavior.
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    ucl_parser_add_string(parser, (char *)data, size);

    if (ucl_parser_get_error(parser) == NULL) {
        ucl_object_t *obj = ucl_parser_get_object(parser);
        if (obj != NULL) {
            ucl_object_unref(obj);
        }
    }

    ucl_parser_free(parser);
    return 0;
}