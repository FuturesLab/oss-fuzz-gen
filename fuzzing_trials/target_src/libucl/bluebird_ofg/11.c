#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_object_t *root = NULL;
    ucl_object_t *new_obj = NULL;
    unsigned int index = 0;

    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    root = ucl_parser_get_object(parser);

    // Create a new UCL object to replace
    new_obj = ucl_object_fromstring("replacement");

    // Ensure root is not NULL and is an array
    if (root != NULL && ucl_object_type(root) == UCL_ARRAY) {
        // Call the function-under-test
        ucl_object_t *result = ucl_array_replace_index(root, new_obj, index);

        // Clean up the result if it's not the same as new_obj
        if (result != new_obj) {
            ucl_object_unref(result);
        }
    }

    // Clean up
    if (root != NULL) {
        ucl_object_unref(root);
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_unref to ucl_object_reserve
        unsigned int ret_ucl_parser_get_column_xfztv = ucl_parser_get_column(parser);
        if (ret_ucl_parser_get_column_xfztv < 0){
        	return 0;
        }
        bool ret_ucl_object_reserve_svzmt = ucl_object_reserve(root, (size_t )ret_ucl_parser_get_column_xfztv);
        if (ret_ucl_object_reserve_svzmt == 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
}
    ucl_object_unref(new_obj);
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

    LLVMFuzzerTestOneInput_11(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
