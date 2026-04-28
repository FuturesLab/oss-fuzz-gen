// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalmemory_resize_buffer at icalmemory.c:329:7 in icalmemory.h
// icalmemory_new_buffer at icalmemory.c:308:7 in icalmemory.h
// icalmemory_tmp_buffer at icalmemory.c:175:7 in icalmemory.h
// icalmemory_append_string at icalmemory.c:358:6 in icalmemory.h
// icalmemory_append_encoded_string at icalmemory.c:476:6 in icalmemory.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test icalmemory_new_buffer
    size_t buffer_size = 10;
    char *buffer = (char *)icalmemory_new_buffer(buffer_size);
    if (!buffer) return 0;

    // Initialize buffer with some data
    strcpy(buffer, "data");
    size_t pos = strlen(buffer);
    char *pos_ptr = buffer + pos;

    // Ensure the input string is null-terminated
    std::string append_str(reinterpret_cast<const char*>(Data), Size);
    
    // Test icalmemory_append_string
    icalmemory_append_string(&buffer, &pos_ptr, &buffer_size, append_str.c_str());

    // Test icalmemory_append_encoded_string
    icalmemory_append_encoded_string(&buffer, &pos_ptr, &buffer_size, append_str.c_str());

    // Test icalmemory_append_char
    char append_char = static_cast<char>(Data[0]);
    icalmemory_append_char(&buffer, &pos_ptr, &buffer_size, append_char);

    // Test icalmemory_resize_buffer
    size_t new_buffer_size = buffer_size + 20;
    char *resized_buffer = (char *)icalmemory_resize_buffer(buffer, new_buffer_size);
    if (resized_buffer) {
        buffer = resized_buffer;
        buffer_size = new_buffer_size;
    }

    // Test icalmemory_tmp_buffer
    char *tmp_buffer = (char *)icalmemory_tmp_buffer(50);
    if (tmp_buffer) {
        strcpy(tmp_buffer, "temporary data");
    }

    // Cleanup
    icalmemory_free_buffer(buffer);

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

        LLVMFuzzerTestOneInput_18(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    