#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Initialize parser and parse input data
    struct ucl_parser *parser = ucl_parser_new(0);
    if (!parser) {
        return 0;
    }

    // Write data to dummy file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_new to ucl_parser_add_fd
    const ucl_object_t cgkjjifd;
    memset(&cgkjjifd, 0, sizeof(cgkjjifd));
    unsigned int ret_ucl_array_size_badne = ucl_array_size(&cgkjjifd);
    if (ret_ucl_array_size_badne < 0){
    	return 0;
    }

    bool ret_ucl_parser_add_fd_crmhg = ucl_parser_add_fd(parser, (int )ret_ucl_array_size_badne);
    if (ret_ucl_parser_add_fd_crmhg == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    write_to_dummy_file(Data, Size);

    // Load data into parser
    ucl_parser_add_file(parser, "./dummy_file");

    // Get comments from parser
    const ucl_object_t *comments = ucl_parser_get_comments(parser);

    // Get the top object
    ucl_object_t *top = ucl_parser_get_object(parser);

    if (top) {
        // Emit object in different formats
        unsigned char *emitted = ucl_object_emit(top, UCL_EMIT_JSON);
        if (emitted) {
            free(emitted);
        }

        emitted = ucl_object_emit(top, UCL_EMIT_CONFIG);
        if (emitted) {
            free(emitted);
        }

        emitted = ucl_object_emit(top, UCL_EMIT_YAML);
        if (emitted) {
            free(emitted);
        }

        emitted = ucl_object_emit(top, UCL_EMIT_MSGPACK);
        if (emitted) {
            free(emitted);
        }

        // Emit object using memory functions
        void *pmem = NULL;
        struct ucl_emitter_functions *emitter_funcs = ucl_object_emit_memory_funcs(&pmem);
        if (emitter_funcs) {
            bool success = ucl_object_emit_full(top, UCL_EMIT_JSON, emitter_funcs, comments);
            if (success && pmem) {
                free(pmem);
            }
            if (emitter_funcs->ucl_emitter_free_func) {
                emitter_funcs->ucl_emitter_free_func(emitter_funcs->ud);
            }
            free(emitter_funcs);
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_emit_memory_funcs to ucl_parser_insert_chunk
        unsigned int ret_ucl_parser_get_linenum_lsofm = ucl_parser_get_linenum(parser);
        if (ret_ucl_parser_get_linenum_lsofm < 0){
        	return 0;
        }
        int ret_ucl_parser_get_default_priority_sydob = ucl_parser_get_default_priority(parser);
        if (ret_ucl_parser_get_default_priority_sydob < 0){
        	return 0;
        }

        bool ret_ucl_parser_insert_chunk_imrzy = ucl_parser_insert_chunk(parser, (const unsigned char *)pmem, (size_t )ret_ucl_parser_get_default_priority_sydob);
        if (ret_ucl_parser_insert_chunk_imrzy == 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_insert_chunk to ucl_object_iterate_safe
        ucl_object_iter_t ret_ucl_object_iterate_new_zbaox = ucl_object_iterate_new(top);

        const ucl_object_t* ret_ucl_object_iterate_safe_fibea = ucl_object_iterate_safe(ret_ucl_object_iterate_new_zbaox, ret_ucl_parser_insert_chunk_imrzy);
        if (ret_ucl_object_iterate_safe_fibea == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        ucl_object_unref(top);
    }

    ucl_parser_free(parser);
    return 0;
}