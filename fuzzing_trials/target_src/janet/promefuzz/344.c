// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_buffer_push_u32 at buffer.c:171:6 in janet.h
// janet_pointer_buffer_unsafe at buffer.c:62:14 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
// janet_buffer_extra at buffer.c:118:6 in janet.h
// janet_buffer at buffer.c:82:14 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
// janet_formatb at janet.c:29462:14 in janet.h
// janet_buffer at buffer.c:82:14 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static void fuzz_janet_buffer_push_u32(JanetBuffer *buffer, const uint8_t *data, size_t size) {
    if (size >= sizeof(uint32_t)) {
        uint32_t x;
        memcpy(&x, data, sizeof(uint32_t));
        janet_buffer_push_u32(buffer, x);
    }
}

static void fuzz_janet_pointer_buffer_unsafe(const uint8_t *data, size_t size) {
    if (size >= sizeof(int32_t) * 2) {
        int32_t capacity, count;
        memcpy(&capacity, data, sizeof(int32_t));
        memcpy(&count, data + sizeof(int32_t), sizeof(int32_t));
        if (count >= 0 && count <= capacity && capacity >= 0) {
            void *memory = malloc(capacity);
            if (memory) {
                JanetBuffer *buffer = janet_pointer_buffer_unsafe(memory, capacity, count);
                if (buffer) {
                    janet_buffer_deinit(buffer);
                }
                free(memory);
            }
        }
    }
}

static void fuzz_janet_buffer_extra(JanetBuffer *buffer, const uint8_t *data, size_t size) {
    if (size >= sizeof(int32_t)) {
        int32_t n;
        memcpy(&n, data, sizeof(int32_t));
        janet_buffer_extra(buffer, n);
    }
}

static void fuzz_janet_buffer(const uint8_t *data, size_t size) {
    if (size >= sizeof(int32_t)) {
        int32_t capacity;
        memcpy(&capacity, data, sizeof(int32_t));
        JanetBuffer *buffer = janet_buffer(capacity);
        if (buffer) {
            janet_buffer_deinit(buffer);
        }
    }
}

static void fuzz_janet_formatb(JanetBuffer *buffer, const uint8_t *data, size_t size) {
    if (size > 0) {
        char *format = (char *)malloc(size + 1);
        if (format) {
            memcpy(format, data, size);
            format[size] = '\0'; // Ensure null-terminated
            janet_formatb(buffer, format);
            free(format);
        }
    }
}

int LLVMFuzzerTestOneInput_344(const uint8_t *Data, size_t Size) {
    initialize_janet();

    JanetBuffer *buffer = janet_buffer(10);
    if (!buffer) return 0;

    fuzz_janet_buffer_push_u32(buffer, Data, Size);
    fuzz_janet_pointer_buffer_unsafe(Data, Size);
    fuzz_janet_buffer_extra(buffer, Data, Size);
    fuzz_janet_buffer(Data, Size);
    fuzz_janet_formatb(buffer, Data, Size);

    janet_buffer_deinit(buffer);
    return 0;
}