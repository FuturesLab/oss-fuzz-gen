// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_buffer_init at buffer.c:54:14 in janet.h
// janet_pointer_buffer_unsafe at buffer.c:62:14 in janet.h
// janet_buffer_extra at buffer.c:118:6 in janet.h
// janet_buffer at buffer.c:82:14 in janet.h
// janet_formatb at janet.c:29462:14 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_173(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for basic operations

    // Initialize the Janet VM
    janet_init();

    // 1. Fuzz janet_buffer_init
    JanetBuffer buffer;
    int32_t capacity = *((int32_t *)Data);
    janet_buffer_init(&buffer, capacity);

    // 2. Fuzz janet_pointer_buffer_unsafe
    if (Size >= 12) {
        void *memory = (void *)(Data + 4);
        int32_t count = *((int32_t *)(Data + 8));
        janet_pointer_buffer_unsafe(memory, capacity, count);
    }

    // 3. Fuzz janet_buffer_extra
    if (Size >= 16) {
        int32_t extra = *((int32_t *)(Data + 12));
        janet_buffer_extra(&buffer, extra);
    }

    // 4. Fuzz janet_buffer
    JanetBuffer *new_buffer = janet_buffer(capacity);

    // 5. Fuzz janet_formatb
    if (Size > 16) {
        const char *format = (const char *)(Data + 16);
        janet_formatb(&buffer, format, "test");
    }

    // 6. Fuzz janet_buffer_deinit
    janet_buffer_deinit(&buffer);
    if (new_buffer) {
        janet_buffer_deinit(new_buffer);
    }

    write_dummy_file(Data, Size);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}