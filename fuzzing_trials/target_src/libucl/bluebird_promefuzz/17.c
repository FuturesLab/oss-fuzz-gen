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

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_emit to ucl_object_replace_key
    ucl_object_t* ret_ucl_array_pop_first_ofojn = ucl_array_pop_first(obj);
    if (ret_ucl_array_pop_first_ofojn == NULL){
    	return 0;
    }
    ucl_object_t* ret_ucl_object_fromdouble_vrsmf = ucl_object_fromdouble(UCL_PRIORITY_MAX);
    if (ret_ucl_object_fromdouble_vrsmf == NULL){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_fromdouble to ucl_array_delete
    ucl_object_t* ret_ucl_array_delete_zeekb = ucl_array_delete(obj, ret_ucl_object_fromdouble_vrsmf);
    if (ret_ucl_array_delete_zeekb == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    unsigned int ret_ucl_object_get_priority_smyzp = ucl_object_get_priority(NULL);
    if (ret_ucl_object_get_priority_smyzp < 0){
    	return 0;
    }
    bool ret_ucl_object_replace_key_tbwmw = ucl_object_replace_key(ret_ucl_array_pop_first_ofojn, ret_ucl_object_fromdouble_vrsmf, (const char *)json_output, (size_t )ret_ucl_object_get_priority_smyzp, 1);
    if (ret_ucl_object_replace_key_tbwmw == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
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
    ucl_object_unref(obj);
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

    LLVMFuzzerTestOneInput_17(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
