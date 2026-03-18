#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *obj = ucl_object_new();
    enum ucl_object_keys_sort_flags sort_flags = UCL_SORT_KEYS_ICASE; // Corrected the enum value

    // Ensure that the data is not empty
    if (size > 0 && obj != NULL) {
        // Create a UCL parser
        struct ucl_parser *parser = ucl_parser_new(0);

        // Parse the input data
        if (ucl_parser_add_chunk(parser, data, size)) {
            // Get the top-level object
            const ucl_object_t *top = ucl_parser_get_object(parser);

            // Copy the parsed object to our object
            ucl_object_merge(obj, (ucl_object_t *)top, true);
        }

        // Free the parser
        ucl_parser_free(parser);

        // Call the function under test
        ucl_object_sort_keys(obj, sort_flags);

        // Clean up
        ucl_object_unref(obj);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif