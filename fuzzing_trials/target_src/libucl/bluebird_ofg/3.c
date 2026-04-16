#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "ucl.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object
    ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Create an iterator
    ucl_object_iter_t iter = ucl_object_iterate_new(root);

    // Choose a valid iterate type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_iterate_new to ucl_object_iterate_reset
    ucl_object_t* ret_ucl_object_fromdouble_cudgk = ucl_object_fromdouble(0);
    if (ret_ucl_object_fromdouble_cudgk == NULL){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_fromdouble to ucl_object_emit_full
    struct ucl_emitter_functions* ret_ucl_object_emit_fd_funcs_dizjd = ucl_object_emit_fd_funcs(0);
    if (ret_ucl_object_emit_fd_funcs_dizjd == NULL){
    	return 0;
    }
    bool ret_ucl_object_emit_full_tuxiq = ucl_object_emit_full(root, 0, ret_ucl_object_emit_fd_funcs_dizjd, ret_ucl_object_fromdouble_cudgk);
    if (ret_ucl_object_emit_full_tuxiq == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_iter_t ret_ucl_object_iterate_reset_degsg = ucl_object_iterate_reset(iter, ret_ucl_object_fromdouble_cudgk);
    // End mutation: Producer.APPEND_MUTATOR
    
    enum ucl_iterate_type iterate_type = UCL_ITERATE_BOTH;

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_iterate_full(iter, iterate_type);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(root);
    ucl_parser_free(parser);

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

    LLVMFuzzerTestOneInput_3(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
