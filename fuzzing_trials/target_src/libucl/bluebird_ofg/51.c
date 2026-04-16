#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "ucl.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for our needs
    if (size < 3) {
        return 0;
    }

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data as a UCL object
    ucl_parser_add_chunk(parser, data, size);
    const ucl_object_t *root = ucl_parser_get_object(parser);

    // Prepare a non-NULL path string and separator
    const char *path = "example.path";
    const char separator = '.';

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup_path_char(root, path, separator);

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    }
    ucl_parser_free(parser);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_51(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
