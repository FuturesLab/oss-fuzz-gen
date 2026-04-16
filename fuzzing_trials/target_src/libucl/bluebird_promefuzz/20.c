#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    // Initialize a UCL parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);

    // Create a dummy file and write the input data to it
    FILE *file = fopen("./dummy_file", "wb");
    if (file == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Parse the dummy file
    if (!ucl_parser_add_file(parser, "./dummy_file")) {
        // Handle parsing error
        ucl_parser_get_error_code(parser);
        ucl_parser_clear_error(parser);
    }

    // Call the target functions in the specified order
    unsigned column = ucl_parser_get_column(parser);
    unsigned linenum = ucl_parser_get_linenum(parser);
    ucl_parser_clear_error(parser);
    int error_code = ucl_parser_get_error_code(parser);
    ucl_object_t *obj = ucl_parser_get_object(parser);

    // If obj is not NULL, unref it once before freeing the parser
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    ucl_parser_free(parser);

    // Clean up the dummy file
    remove("./dummy_file");

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

    LLVMFuzzerTestOneInput_20(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
