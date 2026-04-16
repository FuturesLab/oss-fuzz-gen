#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    struct ucl_parser *parser = ucl_parser_new(0); // Use 'struct' here
    ucl_object_t *obj = NULL;
    const ucl_object_t *result = NULL;
    unsigned int index = 0;

    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    if (ucl_parser_add_chunk(parser, data, size)) {
        obj = ucl_parser_get_object(parser);

        // Ensure the object is an array
        if (obj != NULL && ucl_object_type(obj) == UCL_ARRAY) {
            // Try different indices to find an element
            for (index = 0; index < 5; ++index) {
                result = ucl_array_find_index(obj, index);
            }
        }

        // Free the parsed object
        ucl_object_unref(obj);
    }

    // Clean up the parser
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

    LLVMFuzzerTestOneInput_34(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
