#include <stdint.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);

    // Parse the input data
    if (parser != NULL) {
        ucl_parser_add_chunk(parser, data, size);
        
        // Get the root object
        const ucl_object_t *root = ucl_parser_get_object(parser);
        
        if (root != NULL) {
            // Initialize an iterator
            ucl_object_iter_t iter = ucl_object_iterate_new(root);
            
            // Iterate using ucl_object_iterate_safe
            const ucl_object_t *obj;
            bool expand = true; // or false, try both cases

            while ((obj = ucl_object_iterate_safe(iter, expand)) != NULL) {
                // Process the object if needed
            }
            
            // Free the iterator
            ucl_object_iterate_free(iter);
            
            // Free the root object
            ucl_object_unref(root);
        }
        
        // Clean up the parser
        ucl_parser_free(parser);
    }

    return 0;
}