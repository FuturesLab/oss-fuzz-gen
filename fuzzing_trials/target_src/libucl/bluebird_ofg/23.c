#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "ucl.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
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
            // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ucl_object_merge with ucl_array_merge

            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_object to ucl_object_merge
            bool ret_ucl_object_merge_nlsfz = ucl_object_merge(top, obj, 1);
            if (ret_ucl_object_merge_nlsfz == 0){
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_sort_keys to ucl_object_emit_full
        ucl_object_t* ret_ucl_object_frombool_sislv = ucl_object_frombool(1);
        if (ret_ucl_object_frombool_sislv == NULL){
        	return 0;
        }
        struct ucl_emitter_functions* ret_ucl_object_emit_fd_funcs_bwmob = ucl_object_emit_fd_funcs(UCL_PRIORITY_MIN);
        if (ret_ucl_object_emit_fd_funcs_bwmob == NULL){
        	return 0;
        }
        bool ret_ucl_object_emit_full_lefoi = ucl_object_emit_full(ret_ucl_object_frombool_sislv, 0, ret_ucl_object_emit_fd_funcs_bwmob, obj);
        if (ret_ucl_object_emit_full_lefoi == 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
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

    LLVMFuzzerTestOneInput_23(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
