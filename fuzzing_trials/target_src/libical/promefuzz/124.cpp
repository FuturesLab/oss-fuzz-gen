// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalstrarray_find at icalstrarray.c:35:8 in icalstrarray.h
// icalstrarray_element_at at icalstrarray.c:27:13 in icalstrarray.h
// icalstrarray_remove at icalstrarray.c:91:6 in icalstrarray.h
// icalstrarray_add at icalstrarray.c:66:6 in icalstrarray.h
// icalstrarray_append at icalstrarray.c:54:6 in icalstrarray.h
// icalstrarray_size at icalstrarray.c:19:8 in icalstrarray.h
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalstrarray.h"

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Allocate and initialize an icalstrarray
    icalstrarray array{};
    array.element_size = sizeof(char*);
    array.chunks = nullptr;
    array.space_allocated = 0;
    array.num_elements = 0;
    array.increment_size = 10; // Initialize increment_size to a non-zero value

    // Convert fuzzer data to a string
    std::string input(reinterpret_cast<const char*>(Data), Size);
    const char* cstr = input.c_str();

    // Test icalstrarray_add
    icalstrarray_add(&array, cstr);

    // Test icalstrarray_append
    icalstrarray_append(&array, cstr);

    // Test icalstrarray_size
    size_t size = icalstrarray_size(&array);
    if (size > 0) {
        // Test icalstrarray_element_at
        const char* element = icalstrarray_element_at(&array, 0);
        if (element) {
            // Test icalstrarray_find
            size_t pos = icalstrarray_find(&array, element);
        }
    }

    // Test icalstrarray_remove
    icalstrarray_remove(&array, cstr);

    // Cleanup: Normally, you should free the allocated memory in 'array',
    // but since this is a fuzzing environment, we'll assume the fuzzing
    // infrastructure handles memory cleanup.

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

        LLVMFuzzerTestOneInput_124(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    