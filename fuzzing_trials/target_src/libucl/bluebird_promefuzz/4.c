#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ucl.h"
#include <stdbool.h>

static void dummy_dtor(void *ud) {
    // Dummy destructor
}

static const char *dummy_emitter(void *ud) {
    // Dummy emitter
    return "dummy";
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Fuzz ucl_object_typed_new
    ucl_type_t type = (ucl_type_t)(Data[0] % (UCL_NULL + 1));
    ucl_object_t *obj1 = ucl_object_typed_new(type);

    // Fuzz ucl_object_string_to_type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_typed_new to ucl_object_emit_len
    const ucl_object_t plioetvo;
    memset(&plioetvo, 0, sizeof(plioetvo));
    double ret_ucl_object_todouble_sshdw = ucl_object_todouble(&plioetvo);
    if (ret_ucl_object_todouble_sshdw < 0){
    	return 0;
    }
    unsigned char* ret_ucl_object_emit_len_bleul = ucl_object_emit_len(obj1, 0, (size_t *)&ret_ucl_object_todouble_sshdw);
    if (ret_ucl_object_emit_len_bleul == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    char input[Size + 1];
    memcpy(input, Data, Size);
    input[Size] = '\0';
    ucl_type_t res;
    bool conversion_success = ucl_object_string_to_type(input, &res);

    // Fuzz ucl_object_new_full
    unsigned priority = Data[0];
    ucl_object_t *obj2 = ucl_object_new_full(type, priority);
    if (obj2) {
        ucl_object_unref(obj2);
    }

    // Fuzz ucl_object_type_to_string
    const char *type_str = ucl_object_type_to_string(type);

    // Fuzz ucl_object_new_userdata
    void *user_data = (void *)Data; // Just use the data pointer as user data
    ucl_object_t *obj3 = ucl_object_new_userdata(dummy_dtor, dummy_emitter, user_data);
    if (obj3) {
        ucl_object_unref(obj3);
    }

    // Fuzz ucl_object_type
    if (obj1) {
        ucl_type_t obj_type = ucl_object_type(obj1);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_type to ucl_object_string_to_type
        char* ret_ucl_copy_value_trash_ptqxz = ucl_copy_value_trash(obj1);
        if (ret_ucl_copy_value_trash_ptqxz == NULL){
        	return 0;
        }
        bool ret_ucl_object_string_to_type_qixng = ucl_object_string_to_type(ret_ucl_copy_value_trash_ptqxz, &obj_type);
        if (ret_ucl_object_string_to_type_qixng == 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        ucl_object_unref(obj1);
    }

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

    LLVMFuzzerTestOneInput_4(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
