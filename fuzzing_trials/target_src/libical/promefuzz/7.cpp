// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalmemory_set_mem_alloc_funcs at icalmemory.c:279:6 in icalmemory.h
// icalmemory_free_ring at icalmemory.c:197:6 in icalmemory.h
// icalmemory_free_buffer at icalmemory.c:348:6 in icalmemory.h
// icalmemory_add_tmp_buffer at icalmemory.c:151:6 in icalmemory.h
// icalmemory_append_char at icalmemory.c:399:6 in icalmemory.h
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
#include "icalmemory.h"
}

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

static void custom_free(void *ptr) {
    free(ptr);
}

static void* custom_malloc(size_t size) {
    return malloc(size);
}

static void* custom_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Set custom memory allocation functions
    icalmemory_set_mem_alloc_funcs(custom_malloc, custom_realloc, custom_free);

    // Test icalmemory_add_tmp_buffer and icalmemory_free_ring
    char *buffer = static_cast<char*>(custom_malloc(Size));
    if (buffer) {
        memcpy(buffer, Data, Size);
        icalmemory_add_tmp_buffer(buffer);
        icalmemory_free_ring();
    }

    // Test icalmemory_append_char
    size_t buffer_len = 15;
    char *append_buffer = static_cast<char*>(custom_malloc(buffer_len));
    if (append_buffer) {
        strcpy(append_buffer, "My number is: ");
        size_t buffer_end = strlen(append_buffer);
        char *buffer_end_pos = append_buffer + buffer_end;
        if (buffer_end_pos < append_buffer + buffer_len) {
            icalmemory_append_char(&append_buffer, &buffer_end_pos, &buffer_len, Data[0]);
        }
        icalmemory_free_buffer(append_buffer);
    }

    // Reset memory allocation functions to default
    icalmemory_set_mem_alloc_funcs(nullptr, nullptr, nullptr);

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

        LLVMFuzzerTestOneInput_7(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    