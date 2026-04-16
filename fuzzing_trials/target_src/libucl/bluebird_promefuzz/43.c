#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

static ucl_object_t* create_ucl_object_from_data(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return NULL;
    }
    // Use a portion of data to determine the type
    ucl_type_t type = (ucl_type_t)(Data[0] % (UCL_NULL + 1));
    return ucl_object_typed_new(type);
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a top level UCL object of type UCL_OBJECT
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    if (!top) {
        return 0;
    }

    // Create an element UCL object from input data
    ucl_object_t *element = create_ucl_object_from_data(Data, Size);
    if (!element) {
        ucl_object_unref(top);
        return 0;
    }

    // Use part of the data as a key
    const char *key = (const char *)Data;
    size_t keylen = Size < 256 ? Size : 255; // Limit key length to 255
    bool copy_key = true;

    // Replace key in the top object
    bool replaced = ucl_object_replace_key(top, element, key, keylen, copy_key);

    // Create another element from a string
    ucl_object_t *str_obj = ucl_object_fromstring_common(key, keylen, UCL_STRING_PARSE);
    if (str_obj) {
        ucl_object_insert_key(top, str_obj, "inserted_key_1", 14, true);
    }

    // Insert another element

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_fromstring_common to ucl_array_append
    ucl_object_t* ret_ucl_object_copy_kpcbp = ucl_object_copy(element);
    if (ret_ucl_object_copy_kpcbp == NULL){
    	return 0;
    }
    bool ret_ucl_array_append_jrdqw = ucl_array_append(str_obj, ret_ucl_object_copy_kpcbp);
    if (ret_ucl_array_append_jrdqw == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    ucl_object_t *str_obj2 = ucl_object_fromstring_common(key, keylen, UCL_STRING_PARSE_BOOLEAN);
    if (str_obj2) {
        ucl_object_insert_key(top, str_obj2, "inserted_key_2", 14, true);
    }

    // Insert yet another element
    ucl_object_t *str_obj3 = ucl_object_fromstring_common(key, keylen, UCL_STRING_PARSE_INT);
    if (str_obj3) {
        ucl_object_insert_key(top, str_obj3, "inserted_key_3", 14, true);
    }

    // Create a final UCL object with a specific type
    ucl_object_t *final_obj = ucl_object_typed_new(UCL_STRING);
    if (final_obj) {
        ucl_object_unref(final_obj);
    }

    // Clean up
    ucl_object_unref(top);

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

    LLVMFuzzerTestOneInput_43(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
