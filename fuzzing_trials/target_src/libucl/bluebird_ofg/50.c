#include <sys/stat.h>
#include <string.h>
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // If size is 0, return immediately as we need some data to process
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser;
    const char *cur_file;

    // Create a new UCL parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Call the function-under-test
    cur_file = ucl_parser_get_cur_file(parser);

    // Use the result in some way (e.g., print or check)
    if (cur_file != NULL) {
        // For demonstration purposes, you might print or log the file name
        // printf("Current file: %s\n", cur_file);
    }

    // Free the parser
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

    LLVMFuzzerTestOneInput_50(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
