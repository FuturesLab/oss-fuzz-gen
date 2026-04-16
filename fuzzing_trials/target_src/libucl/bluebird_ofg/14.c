#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "ucl.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *obj = ucl_object_new();

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_new to ucl_object_insert_key
    ucl_object_t zhuvcrbu;
    memset(&zhuvcrbu, 0, sizeof(zhuvcrbu));
    ucl_object_unref(&zhuvcrbu);
    const ucl_object_t jjrdnolf;
    memset(&jjrdnolf, 0, sizeof(jjrdnolf));
    double ret_ucl_object_todouble_kprkw = ucl_object_todouble(&jjrdnolf);
    if (ret_ucl_object_todouble_kprkw < 0){
    	return 0;
    }
    bool ret_ucl_object_insert_key_zyfvj = ucl_object_insert_key(obj, &zhuvcrbu, (const char *)"w", (size_t )ret_ucl_object_todouble_kprkw, 0);
    if (ret_ucl_object_insert_key_zyfvj == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
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
            // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ucl_object_merge with ucl_array_merge

            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_object to ucl_object_merge
            ucl_object_t eavikdnm;
            memset(&eavikdnm, 0, sizeof(eavikdnm));
            bool ret_ucl_object_merge_lwoas = ucl_object_merge(&eavikdnm, top, 1);
            if (ret_ucl_object_merge_lwoas == 0){
            	return 0;
            }
            // End mutation: Producer.APPEND_MUTATOR
            
            ucl_array_merge(obj, (ucl_object_t *)top, true);
            // End mutation: Producer.REPLACE_FUNC_MUTATOR
        
            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_array_merge to ucl_copy_value_trash
            char* ret_ucl_copy_value_trash_sdsey = ucl_copy_value_trash(obj);
            if (ret_ucl_copy_value_trash_sdsey == NULL){
            	return 0;
            }
            // End mutation: Producer.APPEND_MUTATOR
            
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

    LLVMFuzzerTestOneInput_14(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
