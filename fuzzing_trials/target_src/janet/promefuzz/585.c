// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_buffer_push_u8 at buffer.c:156:6 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_buffer_push_string at buffer.c:151:6 in janet.h
// janet_buffer_setcount at buffer.c:105:6 in janet.h
// janet_buffer_push_bytes at buffer.c:144:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_buffer at buffer.c:82:14 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_buffer_push_u8(JanetBuffer *buffer, const uint8_t *data, size_t size) {
    if (size > 0) {
        janet_buffer_push_u8(buffer, data[0]);
    }
}

static void fuzz_janet_buffer_push_string(JanetBuffer *buffer, const uint8_t *data, size_t size) {
    if (size > 0) {
        JanetString string = janet_string(data, size);
        janet_buffer_push_string(buffer, string);
    }
}

static void fuzz_janet_buffer_setcount(JanetBuffer *buffer, const uint8_t *data, size_t size) {
    if (size >= sizeof(int32_t)) {
        int32_t count;
        memcpy(&count, data, sizeof(int32_t));
        janet_buffer_setcount(buffer, count);
    }
}

static void fuzz_janet_buffer_push_bytes(JanetBuffer *buffer, const uint8_t *data, size_t size) {
    if (size > 0) {
        janet_buffer_push_bytes(buffer, data, (int32_t)size);
    }
}

int LLVMFuzzerTestOneInput_585(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    janet_init();

    JanetBuffer *buffer = janet_buffer(10);
    if (!buffer) {
        janet_deinit();
        return 0;
    }

    fuzz_janet_buffer_push_u8(buffer, Data, Size);
    fuzz_janet_buffer_push_string(buffer, Data, Size);
    fuzz_janet_buffer_setcount(buffer, Data, Size);
    fuzz_janet_buffer_push_bytes(buffer, Data, Size);

    janet_buffer_deinit(buffer);
    janet_deinit();
    return 0;
}