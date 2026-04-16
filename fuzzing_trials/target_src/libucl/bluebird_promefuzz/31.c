#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "ucl.h"

static bool dummy_variable_handler(const unsigned char *data, size_t data_len, unsigned char **result, unsigned long *result_len, bool *need_free, void *ud) {
    // Dummy handler function for unknown variables
    *result = NULL;
    *result_len = 0;
    *need_free = false;
    return true;
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Test ucl_parser_add_chunk_full
    ucl_parser_add_chunk_full(parser, Data, Size, 0, UCL_DUPLICATE_APPEND, UCL_PARSE_UCL);

    // Test ucl_parser_set_filevars
    ucl_parser_set_filevars(parser, "./dummy_file", true);

    // Test ucl_parser_set_variables_handler
    ucl_parser_set_variables_handler(parser, dummy_variable_handler, NULL);

    // Test ucl_parser_get_error
    const char *error = ucl_parser_get_error(parser);
    if (error != NULL) {
        printf("Parser error: %s\n", error);
    }

    // Test ucl_parser_clear_error
    ucl_parser_clear_error(parser);

    // Cleanup
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

    LLVMFuzzerTestOneInput_31(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
