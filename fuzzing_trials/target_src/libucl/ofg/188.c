#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
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

    ucl_parser_add_string(parser, (const char *)data, size);

    if (ucl_parser_get_error(parser) == NULL) {
        // Call the function-under-test
        const char *cur_file = ucl_parser_get_cur_file(parser);
        if (cur_file != NULL) {
            printf("Current file: %s\n", cur_file);
        }
    }

    ucl_parser_free(parser);
    return 0;
}