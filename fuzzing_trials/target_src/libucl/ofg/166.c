#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_object_t *root_obj = NULL;
    ucl_object_t *popped_obj = NULL;

    // Ensure that the data is not empty
    if (size > 0) {
        // Parse the input data as a UCL object
        if (ucl_parser_add_chunk(parser, data, size)) {
            root_obj = ucl_parser_get_object(parser);

            // Ensure root_obj is not NULL
            if (root_obj != NULL) {
                // Define a key to pop and ensure it's not NULL
                const char *key = "test_key";
                size_t key_len = 8; // Length of "test_key"

                // Call the function-under-test
                popped_obj = ucl_object_pop_keyl(root_obj, key, key_len);

                // Free the popped object if it exists
                if (popped_obj != NULL) {
                    ucl_object_unref(popped_obj);
                }
            }

            // Free the root object
            ucl_object_unref(root_obj);
        }
    }

    // Clean up the parser
    ucl_parser_free(parser);

    return 0;
}