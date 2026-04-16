#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_buffer_push_u8(JanetBuffer *buffer, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        uint8_t byte = Data[0];
        janet_buffer_push_u8(buffer, byte);
    }
}

static void fuzz_janet_buffer_push_string(JanetBuffer *buffer, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        // Ensure the data is null-terminated for a valid JanetString
        char *tempString = (char *)malloc(Size + 1);
        if (tempString == NULL) return;
        memcpy(tempString, Data, Size);
        tempString[Size] = '\0';
        JanetString string = janet_cstring(tempString);
        janet_buffer_push_string(buffer, string);
        free(tempString);
    }
}

static void fuzz_janet_buffer_push_bytes(JanetBuffer *buffer, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        janet_buffer_push_bytes(buffer, Data, (int32_t)Size);
    }
}

int LLVMFuzzerTestOneInput_1519(const uint8_t *Data, size_t Size) {
    // Initialize the Janet VM before using any Janet functions
    janet_init();

    JanetBuffer *buffer = janet_buffer(10); // Initialize with a small capacity

    if (!buffer) {
        janet_deinit();
        return 0;
    }

    // Fuzz different functions
    fuzz_janet_buffer_push_u8(buffer, Data, Size);
    fuzz_janet_buffer_push_string(buffer, Data, Size);
    fuzz_janet_buffer_push_bytes(buffer, Data, Size);

    janet_buffer_deinit(buffer); // Clean up

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}