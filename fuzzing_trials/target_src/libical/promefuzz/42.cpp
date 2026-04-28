// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalmemory_get_mem_alloc_funcs at icalmemory.c:288:6 in icalmemory.h
// icalmemory_set_mem_alloc_funcs at icalmemory.c:279:6 in icalmemory.h
// icalmemory_strdup at icalmemory.c:235:7 in icalmemory.h
// icalmemory_new_buffer at icalmemory.c:308:7 in icalmemory.h
// icalmemory_free_buffer at icalmemory.c:348:6 in icalmemory.h
// icalmemory_add_tmp_buffer at icalmemory.c:151:6 in icalmemory.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalmemory.h"

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Set custom memory functions
    icalmemory_set_mem_alloc_funcs(malloc, realloc, free);

    // Test icalmemory_strdup with a portion of the input data
    const char *str = reinterpret_cast<const char *>(Data);
    size_t str_len = strnlen(str, Size);
    
    // Ensure null-termination
    char *null_terminated_str = static_cast<char *>(malloc(str_len + 1));
    if (null_terminated_str) {
        memcpy(null_terminated_str, str, str_len);
        null_terminated_str[str_len] = '\0';  // Null-terminate the string

        char *dup_str = icalmemory_strdup(null_terminated_str);
        if (dup_str) {
            icalmemory_free_buffer(dup_str);
        }
        free(null_terminated_str);
    }

    // Test icalmemory_new_buffer and icalmemory_free_buffer
    void *buffer = icalmemory_new_buffer(Size);
    if (buffer) {
        memcpy(buffer, Data, Size);
        icalmemory_free_buffer(buffer);
    }

    // Test icalmemory_add_tmp_buffer
    void *tmp_buffer = malloc(Size);
    if (tmp_buffer) {
        memcpy(tmp_buffer, Data, Size);
        icalmemory_add_tmp_buffer(tmp_buffer);
    }

    // Retrieve memory functions to ensure they are set correctly
    icalmemory_malloc_f f_malloc;
    icalmemory_realloc_f f_realloc;
    icalmemory_free_f f_free;
    icalmemory_get_mem_alloc_funcs(&f_malloc, &f_realloc, &f_free);

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

        LLVMFuzzerTestOneInput_42(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    