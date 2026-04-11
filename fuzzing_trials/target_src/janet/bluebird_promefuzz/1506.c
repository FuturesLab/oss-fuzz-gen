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

static void fuzz_janet_string_begin(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t length;
    memcpy(&length, Data, sizeof(int32_t));
    if (length < 0) return;
    uint8_t *str = janet_string_begin(length);
    // No need to free str as it is managed by Janet's garbage collector
}

static void fuzz_janet_buffer_setcount(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t count;
    memcpy(&count, Data, sizeof(int32_t));
    JanetBuffer buffer = {0};
    janet_buffer_setcount(&buffer, count);
    if (buffer.data) {
        free(buffer.data);
    }
}

static void fuzz_janet_buffer_ensure(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int32_t)) return;
    int32_t capacity, growth;
    memcpy(&capacity, Data, sizeof(int32_t));
    memcpy(&growth, Data + sizeof(int32_t), sizeof(int32_t));
    if (capacity < 0 || growth <= 0) return;
    JanetBuffer buffer = {0};
    janet_buffer_ensure(&buffer, capacity, growth);
    if (buffer.data) {
        free(buffer.data);
    }
}

static void fuzz_janet_string(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t len;
    memcpy(&len, Data, sizeof(int32_t));
    if (len < 0 || (size_t)len > Size - sizeof(int32_t)) return;
    JanetString str = janet_string(Data + sizeof(int32_t), len);
    // No need to free str as it is managed by Janet's garbage collector
}

static void fuzz_janet_buffer_push_bytes(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t len;
    memcpy(&len, Data, sizeof(int32_t));
    if (len < 0 || (size_t)len > Size - sizeof(int32_t)) return;
    JanetBuffer buffer = {0};
    janet_buffer_push_bytes(&buffer, Data + sizeof(int32_t), len);
    if (buffer.data) {
        free(buffer.data);
    }
}

int LLVMFuzzerTestOneInput_1506(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_string_begin(Data, Size);
    fuzz_janet_buffer_setcount(Data, Size);
    fuzz_janet_buffer_ensure(Data, Size);
    fuzz_janet_string(Data, Size);
    fuzz_janet_buffer_push_bytes(Data, Size);
    return 0;
}