#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "ucl.h"

static ucl_object_t *create_random_ucl_array(const uint8_t *Data, size_t Size) {
    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
    for (size_t i = 0; i < Size; i++) {
        ucl_object_t *obj = ucl_object_fromint(Data[i]);
        ucl_array_append(array, obj);
    }
    return array;
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    ucl_object_t *array = create_random_ucl_array(Data, Size);

    // Fuzz ucl_array_replace_index
    ucl_object_t *new_element = ucl_object_fromint(Data[0]);
    unsigned int index = Data[0] % Size;
    ucl_object_t *replaced = ucl_array_replace_index(array, new_element, index);
    if (replaced) {
        ucl_object_unref(replaced);
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_unref to ucl_array_replace_index
        ucl_object_t* ret_ucl_object_fromstring_nasge = ucl_object_fromstring((const char *)"r");
        if (ret_ucl_object_fromstring_nasge == NULL){
        	return 0;
        }
        double ret_ucl_object_todouble_vripy = ucl_object_todouble(new_element);
        if (ret_ucl_object_todouble_vripy < 0){
        	return 0;
        }
        ucl_object_t* ret_ucl_array_replace_index_zuubv = ucl_array_replace_index(ret_ucl_object_fromstring_nasge, replaced, (unsigned int )ret_ucl_object_todouble_vripy);
        if (ret_ucl_array_replace_index_zuubv == NULL){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
}

    // Fuzz ucl_array_pop_first
    ucl_object_t *first = ucl_array_pop_first(array);
    if (first) {
        ucl_object_unref(first);
    }

    // Fuzz ucl_array_size
    unsigned int size = ucl_array_size(array);

    // Fuzz ucl_array_find_index
    const ucl_object_t *found = ucl_array_find_index(array, index);

    // Fuzz ucl_array_index_of
    unsigned int index_of = ucl_array_index_of(array, new_element);

    // Fuzz ucl_array_pop_last
    ucl_object_t *last = ucl_array_pop_last(array);
    if (last) {
        ucl_object_unref(last);
    }

    // Cleanup
    ucl_object_unref(array);
    // new_element is already part of the array, no need to unref again

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

    LLVMFuzzerTestOneInput_47(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
