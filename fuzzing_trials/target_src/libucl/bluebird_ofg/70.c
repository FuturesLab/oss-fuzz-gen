#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "ucl.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *obj = ucl_object_new();
    enum ucl_object_keys_sort_flags sort_flags = UCL_SORT_KEYS_ICASE; // Corrected the enum value

    // Ensure that the data is not empty
    if (size > 0 && obj != NULL) {
        // Create a UCL parser
        struct ucl_parser *parser = ucl_parser_new(0);

        // Parse the input data
        if (ucl_parser_add_chunk(parser, data, size)) {
            // Get the top-level object
            const ucl_object_t *top = ucl_parser_get_object(parser);

            // Copy the parsed object to our object
            ucl_object_merge(obj, (ucl_object_t *)top, true);
        }

        // Free the parser
        ucl_parser_free(parser);

        // Call the function under test
        ucl_object_sort_keys(obj, sort_flags);

        // Clean up
        ucl_object_unref(obj);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
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

    LLVMFuzzerTestOneInput_70(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
