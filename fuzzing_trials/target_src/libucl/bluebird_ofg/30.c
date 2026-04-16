#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *obj = ucl_object_new();
    ucl_emitter_t emitter = UCL_EMIT_JSON_COMPACT;
    unsigned char *result;

    // Ensure the data is not empty
    if (size > 0) {
        // Create a UCL parser
        struct ucl_parser *parser = ucl_parser_new(0);

        // Feed data to the parser
        if (ucl_parser_add_chunk(parser, data, size)) {
            // Get the UCL object
            obj = ucl_parser_get_object(parser);
        }

        // Free the parser
        ucl_parser_free(parser);
    }

    // Call the function-under-test
    result = ucl_object_emit(obj, emitter);

    // Clean up
    if (result != NULL) {
        ucl_object_unref(obj);
    }

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

    LLVMFuzzerTestOneInput_30(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
