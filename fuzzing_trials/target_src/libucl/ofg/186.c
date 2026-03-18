#include <stddef.h>
#include <stdint.h>
#include <ucl.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    const ucl_object_t *root_obj = NULL;
    const ucl_object_t *result_obj = NULL;
    char *key = NULL;
    
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Parse the input data as UCL
    if (ucl_parser_add_chunk(parser, data, size)) {
        root_obj = ucl_parser_get_object(parser);
    }

    // Ensure root_obj is not NULL
    if (root_obj != NULL) {
        // Use a portion of the data as a key
        size_t key_length = size < 256 ? size : 256; // Limit key length
        key = (char*)malloc(key_length + 1);
        if (key != NULL) {
            memcpy(key, data, key_length);
            key[key_length] = '\0'; // Null-terminate the key

            // Call the function-under-test
            result_obj = ucl_object_lookup_any(root_obj, key, (void*)data);
        }
    }

    // Clean up
    if (root_obj != NULL) {
        ucl_object_unref(root_obj);
    }
    ucl_parser_free(parser);
    if (key != NULL) {
        free(key);
    }

    return 0;
}