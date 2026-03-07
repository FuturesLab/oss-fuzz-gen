#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize a ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);

    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Add data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object
    const ucl_object_t *obj = ucl_parser_get_object(parser);

    // Create an iterator
    ucl_object_iter_t iter = ucl_object_iterate_new(obj);

    // Call the function under test
    bool result = ucl_object_iter_chk_excpn(&iter);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}