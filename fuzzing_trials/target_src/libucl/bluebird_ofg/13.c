#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *ucl_obj = NULL;
    ucl_emitter_t emitter_type = UCL_EMIT_JSON; // Corrected type name

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the UCL object
    ucl_obj = ucl_parser_get_object(parser);
    if (ucl_obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    unsigned char *result = ucl_object_emit(ucl_obj, emitter_type);

    // Free allocated resources
    if (result != NULL) {
        free(result);
    }
    ucl_object_unref(ucl_obj);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_unref to ucl_elt_append

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_unref to ucl_array_prepend
    ucl_object_t* ret_ucl_array_pop_last_tegih = ucl_array_pop_last(ucl_obj);
    if (ret_ucl_array_pop_last_tegih == NULL){
    	return 0;
    }
    bool ret_ucl_array_prepend_ugfvm = ucl_array_prepend(ucl_obj, ret_ucl_array_pop_last_tegih);
    if (ret_ucl_array_prepend_ugfvm == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_t* ret_ucl_object_fromdouble_hdhsj = ucl_object_fromdouble(size);
    if (ret_ucl_object_fromdouble_hdhsj == NULL){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_fromdouble to ucl_object_toint_safe
    const ucl_object_t qtrywote;
    memset(&qtrywote, 0, sizeof(qtrywote));
    int64_t ret_ucl_object_toint_nhyra = ucl_object_toint(&qtrywote);
    if (ret_ucl_object_toint_nhyra < 0){
    	return 0;
    }
    bool ret_ucl_object_toint_safe_hlejn = ucl_object_toint_safe(ret_ucl_object_fromdouble_hdhsj, &ret_ucl_object_toint_nhyra);
    if (ret_ucl_object_toint_safe_hlejn == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_t* ret_ucl_elt_append_efsbd = ucl_elt_append(ucl_obj, ret_ucl_object_fromdouble_hdhsj);
    if (ret_ucl_elt_append_efsbd == NULL){
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

    LLVMFuzzerTestOneInput_13(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
