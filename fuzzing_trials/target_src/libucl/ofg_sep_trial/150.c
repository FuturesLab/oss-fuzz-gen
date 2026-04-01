#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize a ucl_parser and add data to it
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object from the parser
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);
    if (root_obj != NULL) {
        // Call the function under test
        ucl_object_iter_t iter = ucl_object_iterate_new(root_obj);

        // Normally, we would use the iterator here, but for fuzzing, we just ensure it is created
        (void)iter; // Suppress unused variable warning
    }

    // Clean up
    ucl_object_unref(root_obj);
    ucl_parser_free(parser);

    return 0;
}