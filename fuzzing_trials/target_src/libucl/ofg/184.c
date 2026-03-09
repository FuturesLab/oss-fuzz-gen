#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    ucl_object_t *root = NULL;
    struct ucl_parser *parser = ucl_parser_new(0); // Use 'struct' tag for ucl_parser
    const ucl_object_t *result = NULL;
    char *key = NULL;
    void *dummy = (void *)1; // Non-NULL dummy pointer

    // Ensure size is greater than 0 to create a valid key
    if (size == 0) {
        return 0;
    }

    // Parse the input data into a UCL object
    if (ucl_parser_add_chunk(parser, data, size)) {
        root = ucl_parser_get_object(parser);
    }

    // Create a key from the input data
    key = (char *)malloc(size + 1);
    if (key != NULL) {
        memcpy(key, data, size);
        key[size] = '\0'; // Null-terminate the key

        // Call the function-under-test
        result = ucl_object_lookup_any(root, key, dummy);

        free(key);
    }

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    }
    ucl_parser_free(parser);

    return 0;
}