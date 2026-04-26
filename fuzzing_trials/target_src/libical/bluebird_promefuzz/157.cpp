#include <sys/stat.h>
#include <string.h>
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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalstrarray.h"

extern "C" int LLVMFuzzerTestOneInput_157(const uint8_t *Data, size_t Size) {
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_157(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
