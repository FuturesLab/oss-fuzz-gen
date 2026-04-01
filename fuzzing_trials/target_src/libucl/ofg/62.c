#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated before parsing
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data
    if (!ucl_parser_add_string(parser, input_data, size)) {
        free(input_data);
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);
    if (root_obj == NULL) {
        free(input_data);
        ucl_parser_free(parser);
        return 0;
    }

    // Define a path to lookup
    const char *path = "example.path";

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup_path(root_obj, path);

    // Free resources
    ucl_object_unref(root_obj);
    free(input_data);
    ucl_parser_free(parser);

    return 0;
}