// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_buffer at buffer.c:82:14 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_buffer_setcount at buffer.c:105:6 in janet.h
// janet_buffer_ensure at buffer.c:88:6 in janet.h
// janet_buffer_extra at buffer.c:118:6 in janet.h
// janet_buffer_push_bytes at buffer.c:144:6 in janet.h
// janet_pointer_buffer_unsafe at buffer.c:62:14 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void initialize_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_658(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    janet_init();

    int32_t capacity = *(int32_t *)Data;
    Data += 4;
    Size -= 4;

    JanetBuffer *buffer = janet_buffer(capacity);
    if (!buffer) {
        janet_deinit();
        return 0;
    }

    if (Size >= 4) {
        int32_t count = *(int32_t *)Data;
        janet_buffer_setcount(buffer, count);
        Data += 4;
        Size -= 4;
    }

    if (Size >= 8) {
        int32_t new_capacity = *(int32_t *)Data;
        int32_t growth = *(int32_t *)(Data + 4);
        janet_buffer_ensure(buffer, new_capacity, growth);
        Data += 8;
        Size -= 8;
    }

    if (Size >= 4) {
        int32_t extra = *(int32_t *)Data;
        janet_buffer_extra(buffer, extra);
        Data += 4;
        Size -= 4;
    }

    if (Size > 0) {
        janet_buffer_push_bytes(buffer, Data, (int32_t)Size);
    }

    if (Size >= 12) {
        void *memory = malloc(capacity);
        if (memory) {
            memcpy(memory, Data, capacity);
            int32_t mem_capacity = *(int32_t *)Data;
            int32_t mem_count = *(int32_t *)(Data + 4);
            janet_pointer_buffer_unsafe(memory, mem_capacity, mem_count);
            free(memory);
        }
    }

    initialize_dummy_file(Data, Size);

    janet_deinit();

    return 0;
}