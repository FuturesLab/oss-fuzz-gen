// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalenumarray_free at icalenumarray.c:132:6 in icalenumarray.h
// icalarray_copy at icalarray.c:60:12 in icalarray.h
// icalenumarray_clone at icalenumarray.c:155:16 in icalenumarray.h
// icalarray_free at icalarray.c:95:6 in icalarray.h
// icalenumarray_append at icalenumarray.c:75:6 in icalenumarray.h
// icalenumarray_sort at icalenumarray.c:146:6 in icalenumarray.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalenumarray.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalarray.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

static icalenumarray* create_test_icalenumarray(size_t element_size, size_t num_elements) {
    icalenumarray* array = static_cast<icalenumarray*>(malloc(sizeof(icalenumarray)));
    if (!array) return nullptr;
    
    array->element_size = element_size;
    array->chunks = static_cast<void**>(malloc(num_elements * sizeof(void*)));
    if (!array->chunks) {
        free(array);
        return nullptr;
    }
    
    for (size_t i = 0; i < num_elements; ++i) {
        array->chunks[i] = malloc(element_size);
        if (!array->chunks[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(array->chunks[j]);
            }
            free(array->chunks);
            free(array);
            return nullptr;
        }
        memset(array->chunks[i], i, element_size); // Fill with some data
    }
    
    return array;
}

static void free_test_icalenumarray(icalenumarray* array, size_t num_elements) {
    if (!array) return;
    if (array->chunks) {
        for (size_t i = 0; i < num_elements; ++i) {
            free(array->chunks[i]);
        }
        free(array->chunks);
    }
    free(array);
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t) * 2) return 0;

    size_t element_size = reinterpret_cast<const size_t*>(Data)[0];
    size_t num_elements = reinterpret_cast<const size_t*>(Data)[1];
    if (element_size == 0 || num_elements == 0) return 0;

    icalenumarray* array = create_test_icalenumarray(element_size, num_elements);
    if (!array) return 0;

    // Test icalenumarray_sort
    icalenumarray_sort(array);

    // Test icalenumarray_clone
    icalenumarray* cloned_array = icalenumarray_clone(array);
    if (cloned_array) {
        icalenumarray_free(cloned_array);
    }

    // Test icalarray_copy
    icalarray* copied_array = icalarray_copy(reinterpret_cast<icalarray*>(array));
    if (copied_array) {
        icalarray_free(copied_array);
    }

    // Test icalenumarray_append
    icalenumarray_element elem;
    icalenumarray_append(array, &elem);

    // Cleanup
    free_test_icalenumarray(array, num_elements);

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

        LLVMFuzzerTestOneInput_38(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    