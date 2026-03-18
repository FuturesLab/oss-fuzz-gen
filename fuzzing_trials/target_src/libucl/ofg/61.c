#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to split into a path and data
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts: one for the path and one for the UCL object
    size_t path_size = size / 2;
    size_t ucl_data_size = size - path_size;

    // Create a null-terminated string for the path
    char *path = (char *)malloc(path_size + 1);
    if (path == NULL) {
        return 0;
    }
    memcpy(path, data, path_size);
    path[path_size] = '\0';

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        free(path);
        return 0;
    }

    // Parse the UCL data
    ucl_parser_add_chunk(parser, data + path_size, ucl_data_size);

    // Get the root UCL object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root != NULL) {
        // Call the function-under-test
        const ucl_object_t *result = ucl_object_lookup_path(root, path);

        // Optionally, perform some checks or operations with 'result'
        (void)result; // Suppress unused variable warning
    }

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);
    free(path);

    return 0;
}