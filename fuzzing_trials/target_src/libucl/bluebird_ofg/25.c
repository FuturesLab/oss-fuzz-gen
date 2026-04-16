#include <sys/stat.h>
#include <string.h>
#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data as a string to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object from the parser
    const ucl_object_t *root = ucl_parser_get_object(parser);

    if (root != NULL) {
        // Call the function under test
        const ucl_object_t *head = ucl_array_head(root);

        // Do something with the result to prevent compiler optimizations
        if (head != NULL) {
            // Dummy operation
            (void)ucl_object_tostring(head);
        }
    }

    // Free the parser and the root object
    ucl_object_unref(root);
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

    LLVMFuzzerTestOneInput_25(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
