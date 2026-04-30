// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icallangbind_access_array at icallangbind.c:32:5 in icallangbind.h
// icallangbind_free_array at icallangbind.c:27:6 in icallangbind.h
// icallangbind_new_array at icallangbind.c:20:6 in icallangbind.h
// icalmemory_new_buffer at icalmemory.c:308:7 in icalmemory.h
// icalmemory_free_buffer at icalmemory.c:348:6 in icalmemory.h
// icalmemory_resize_buffer at icalmemory.c:329:7 in icalmemory.h
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
#include "icalmemory.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icallangbind.h"

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int) + sizeof(int)) {
        return 0;
    }

    // Allocate a new buffer using icalmemory_new_buffer
    size_t buffer_size = static_cast<size_t>(Data[0]);
    void *buffer = icalmemory_new_buffer(buffer_size);

    if (buffer) {
        // Resize the buffer using icalmemory_resize_buffer
        size_t new_size = static_cast<size_t>(Data[1]);
        void *resized_buffer = icalmemory_resize_buffer(buffer, new_size);

        if (resized_buffer) {
            // Free the resized buffer
            icalmemory_free_buffer(resized_buffer);
        } else {
            // Free the original buffer if resizing failed
            icalmemory_free_buffer(buffer);
        }
    }

    // Create a new array using icallangbind_new_array
    unsigned int array_size = *reinterpret_cast<const unsigned int*>(Data);
    int *array = icallangbind_new_array(array_size);

    if (array) {
        // Access an element from the array using icallangbind_access_array
        int index = *reinterpret_cast<const int*>(Data + sizeof(unsigned int));
        int value = icallangbind_access_array(array, index);

        // Avoid unused variable warning
        (void)value;

        // Free the array using icallangbind_free_array
        icallangbind_free_array(array);
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

        LLVMFuzzerTestOneInput_94(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    