// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalstrarray_sort at icalstrarray.c:132:6 in icalstrarray.h
// icalarray_copy at icalarray.c:60:12 in icalarray.h
// icalarray_free at icalarray.c:95:6 in icalarray.h
// icalarray_set_element_at at icalarray.c:134:6 in icalarray.h
// icalarray_element_at at icalarray.c:126:7 in icalarray.h
// icalstrarray_size at icalstrarray.c:19:8 in icalstrarray.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalarray.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalstrarray.h"

static icalarray* create_test_icalarray(size_t element_size, size_t num_elements) {
    icalarray* array = icalarray_new(element_size, 1);
    if (!array) return nullptr;
    for (size_t i = 0; i < num_elements; ++i) {
        int value = static_cast<int>(i);
        icalarray_append(array, &value);
    }
    return array;
}

static icalstrarray* create_test_icalstrarray(size_t num_elements) {
    icalstrarray* array = icalarray_new(sizeof(char*), 1);
    if (!array) return nullptr;
    for (size_t i = 0; i < num_elements; ++i) {
        const char* str = "test";
        icalarray_append(array, &str);
    }
    return array;
}

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create and manipulate icalarray
    icalarray* array = create_test_icalarray(sizeof(int), Size);
    if (array) {
        if (Size > 0) {
            int new_element = 42;
            icalarray_set_element_at(array, &new_element, 0);
            int* element = static_cast<int*>(icalarray_element_at(array, 0));
            if (element) {
                *element = 99;
            }
        }

        icalarray* copied_array = icalarray_copy(array);
        if (copied_array) {
            icalarray_free(copied_array);
        }

        icalarray_free(array);
    }

    // Create and manipulate icalstrarray
    icalstrarray* str_array = create_test_icalstrarray(Size);
    if (str_array) {
        icalstrarray_sort(str_array);
        size_t str_array_size = icalstrarray_size(str_array);
        (void)str_array_size; // To avoid unused variable warning

        icalarray_free(str_array);
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

        LLVMFuzzerTestOneInput_99(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    