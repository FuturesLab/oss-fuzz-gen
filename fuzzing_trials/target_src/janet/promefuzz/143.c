// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_buffer_init at buffer.c:54:14 in janet.h
// janet_formatbv at janet.c:29303:6 in janet.h
// janet_buffer_setcount at buffer.c:105:6 in janet.h
// janet_buffer_push_cstring at buffer.c:138:6 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void fuzz_janet_buffer_init(JanetBuffer *buffer, int32_t capacity) {
    janet_buffer_init(buffer, capacity);
}

static void fuzz_janet_formatbv(JanetBuffer *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    janet_formatbv(buffer, format, args);
    va_end(args);
}

static void fuzz_janet_buffer_setcount(JanetBuffer *buffer, int32_t count) {
    janet_buffer_setcount(buffer, count);
}

static void fuzz_janet_buffer_push_cstring(JanetBuffer *buffer, const char *cstring) {
    janet_buffer_push_cstring(buffer, cstring);
}

static void fuzz_janet_buffer_deinit(JanetBuffer *buffer) {
    janet_buffer_deinit(buffer);
}

int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    // Initialize the Janet VM
    janet_init();

    int32_t capacity = *(int32_t *)Data;
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    JanetBuffer buffer;
    fuzz_janet_buffer_init(&buffer, capacity);

    if (Size > 0) {
        fuzz_janet_buffer_setcount(&buffer, Data[0]);
    }

    if (Size > 1) {
        size_t format_len = strnlen((const char *)(Data + 1), Size - 1);
        char *format = (char *)malloc(format_len + 1);
        if (format) {
            memcpy(format, Data + 1, format_len);
            format[format_len] = '\0';
            fuzz_janet_formatbv(&buffer, format, 42, 'A', 1234);
            free(format);
        }
    }

    if (Size > 2) {
        size_t cstring_len = strnlen((const char *)(Data + 2), Size - 2);
        char *cstring = (char *)malloc(cstring_len + 1);
        if (cstring) {
            memcpy(cstring, Data + 2, cstring_len);
            cstring[cstring_len] = '\0';
            fuzz_janet_buffer_push_cstring(&buffer, cstring);
            free(cstring);
        }
    }

    fuzz_janet_buffer_deinit(&buffer);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}