// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_buffer_init at buffer.c:54:14 in janet.h
// janet_buffer_init at buffer.c:54:14 in janet.h
// janet_buffer_setcount at buffer.c:105:6 in janet.h
// janet_pointer_buffer_unsafe at buffer.c:62:14 in janet.h
// janet_buffer_init at buffer.c:54:14 in janet.h
// janet_buffer_ensure at buffer.c:88:6 in janet.h
// janet_buffer_init at buffer.c:54:14 in janet.h
// janet_buffer_extra at buffer.c:118:6 in janet.h
// janet_buffer at buffer.c:82:14 in janet.h
// janet_buffer_setcount at buffer.c:105:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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

static void fuzz_janet_buffer_init(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;

    int32_t capacity;
    memcpy(&capacity, Data, sizeof(int32_t));

    JanetBuffer buffer;
    janet_buffer_init(&buffer, capacity);
}

static void fuzz_janet_buffer_setcount(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return;

    int32_t capacity, count;
    memcpy(&capacity, Data, sizeof(int32_t));
    memcpy(&count, Data + sizeof(int32_t), sizeof(int32_t));

    JanetBuffer buffer;
    janet_buffer_init(&buffer, capacity);
    janet_buffer_setcount(&buffer, count);
}

static void fuzz_janet_pointer_buffer_unsafe(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return;

    int32_t capacity, count;
    memcpy(&capacity, Data, sizeof(int32_t));
    memcpy(&count, Data + sizeof(int32_t), sizeof(int32_t));

    if (Size < sizeof(int32_t) * 2 + capacity) return;

    void *memory = malloc(capacity);
    if (!memory) return;
    memcpy(memory, Data + sizeof(int32_t) * 2, capacity);

    janet_pointer_buffer_unsafe(memory, capacity, count);

    free(memory);
}

static void fuzz_janet_buffer_ensure(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return;

    int32_t capacity, growth;
    memcpy(&capacity, Data, sizeof(int32_t));
    memcpy(&growth, Data + sizeof(int32_t), sizeof(int32_t));

    JanetBuffer buffer;
    janet_buffer_init(&buffer, capacity);
    janet_buffer_ensure(&buffer, capacity, growth);
}

static void fuzz_janet_buffer_extra(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return;

    int32_t capacity, n;
    memcpy(&capacity, Data, sizeof(int32_t));
    memcpy(&n, Data + sizeof(int32_t), sizeof(int32_t));

    JanetBuffer buffer;
    janet_buffer_init(&buffer, capacity);
    janet_buffer_extra(&buffer, n);
}

static void fuzz_janet_buffer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;

    int32_t capacity;
    memcpy(&capacity, Data, sizeof(int32_t));

    JanetBuffer *buffer = janet_buffer(capacity);
    if (buffer) {
        janet_buffer_setcount(buffer, capacity / 2);
    }
}

int LLVMFuzzerTestOneInput_460(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_buffer_init(Data, Size);
    fuzz_janet_buffer_setcount(Data, Size);
    fuzz_janet_pointer_buffer_unsafe(Data, Size);
    fuzz_janet_buffer_ensure(Data, Size);
    fuzz_janet_buffer_extra(Data, Size);
    fuzz_janet_buffer(Data, Size);
    return 0;
}