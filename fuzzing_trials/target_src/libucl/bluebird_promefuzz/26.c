#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Step 1: Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Step 2: Add chunk to the parser
    if (!ucl_parser_add_chunk(parser, Data, Size)) {
        // Handle parsing error
        const char *error = ucl_parser_get_error(parser);
        if (error != NULL) {
            // Normally, you might log the error, but for fuzzing, we ignore it
        }
        ucl_parser_free(parser);
        return 0;
    }

    // Step 3: Get the top-level object
    ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj == NULL) {
        // Handle error in getting object
        const char *error = ucl_parser_get_error(parser);
        if (error != NULL) {
            // Normally, you might log the error, but for fuzzing, we ignore it
        }
        ucl_parser_free(parser);
        return 0;
    }

    // Step 4: Serialize the object in various formats
    unsigned char *json_output = ucl_object_emit(obj, UCL_EMIT_JSON);
    if (json_output != NULL) {
        free(json_output);
    }

    unsigned char *config_output = ucl_object_emit(obj, UCL_EMIT_CONFIG);
    if (config_output != NULL) {
        free(config_output);
    }

    unsigned char *yaml_output = ucl_object_emit(obj, UCL_EMIT_YAML);
    if (yaml_output != NULL) {
        free(yaml_output);
    }

    unsigned char *msgpack_output = ucl_object_emit(obj, UCL_EMIT_MSGPACK);
    if (msgpack_output != NULL) {
        free(msgpack_output);
    }

    // Step 5: Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_emit to ucl_comments_add
    ucl_object_t* ret_ucl_array_pop_last_qxpyy = ucl_array_pop_last(obj);
    if (ret_ucl_array_pop_last_qxpyy == NULL){
    	return 0;
    }
    ucl_object_t* ret_ucl_object_fromdouble_ozslk = ucl_object_fromdouble(-1);
    if (ret_ucl_object_fromdouble_ozslk == NULL){
    	return 0;
    }
    ucl_comments_add(obj, ret_ucl_object_fromdouble_ozslk, (const char *)json_output);
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_unref(obj);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_unref to ucl_array_tail
    const ucl_object_t* ret_ucl_array_tail_kfrco = ucl_array_tail(obj);
    if (ret_ucl_array_tail_kfrco == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_26(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
