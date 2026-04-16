#include <sys/stat.h>
#include <string.h>
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    const ucl_object_t *root = NULL;
    const ucl_object_t *comment = NULL;
    
    // Ensure the data is not empty
    if (size == 0) {
        ucl_parser_free(parser);
        return 0;
    }

    // Parse the input data
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    root = ucl_parser_get_object(parser);

    // Create a dummy key object to search for comments

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_object to ucl_array_merge
    ucl_object_t* ret_ucl_object_ref_ifzmf = ucl_object_ref(root);
    if (ret_ucl_object_ref_ifzmf == NULL){
    	return 0;
    }
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of ucl_array_merge
    bool ret_ucl_array_merge_gnfhw = ucl_array_merge(root, ret_ucl_object_ref_ifzmf, 1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (ret_ucl_array_merge_gnfhw == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_t *key = ucl_object_fromstring("dummy_key");

    // Call the function-under-test
    comment = ucl_comments_find(root, key);

    // Clean up
    ucl_object_unref(root);
    ucl_object_unref(key);
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

    LLVMFuzzerTestOneInput_28(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
