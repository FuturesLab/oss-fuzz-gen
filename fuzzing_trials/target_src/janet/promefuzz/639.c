// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_string at string.c:49:16 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_buffer_push_string at buffer.c:151:6 in janet.h
// janet_string_equal at string.c:82:5 in janet.h
// janet_ev_sendto_string at janet.c:11767:22 in janet.h
// janet_ev_send_string at janet.c:11759:22 in janet.h
// janet_ev_write_string at janet.c:11750:22 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "janet.h"

// Helper function to create a JanetString from raw data
static JanetString create_janet_string(const uint8_t *data, size_t size) {
    return janet_string(data, size);
}

// Helper function to initialize a JanetBuffer
static void init_janet_buffer(JanetBuffer *buffer) {
    buffer->count = 0;
    buffer->capacity = 32;
    buffer->data = (uint8_t *)malloc(buffer->capacity);
}

// Helper function to initialize a JanetStream
static void init_janet_stream(JanetStream *stream) {
    memset(stream, 0, sizeof(JanetStream));
    stream->handle = -1; // Invalid handle to prevent accidental use
}

int LLVMFuzzerTestOneInput_639(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet runtime
    janet_init();

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    init_janet_buffer(&buffer);

    // Create a JanetString from the input data
    JanetString string = create_janet_string(Data, Size);

    // Fuzz janet_buffer_push_string
    janet_buffer_push_string(&buffer, string);

    // Fuzz janet_string_equal by comparing the string with itself
    int is_equal = janet_string_equal(string, string);

    // Prepare a dummy JanetStream
    JanetStream stream;
    init_janet_stream(&stream);

    // Fuzz janet_ev_sendto_string
    // Ensure stream is set up properly for testing
    if (stream.handle != -1) {
        janet_ev_sendto_string(&stream, string, NULL, 0);
    }

    // Fuzz janet_ev_send_string
    if (stream.handle != -1) {
        janet_ev_send_string(&stream, string, 0);
    }

    // Fuzz janet_ev_write_string
    if (stream.handle != -1) {
        janet_ev_write_string(&stream, string);
    }

    // Cleanup
    free(buffer.data);

    // Deinitialize Janet runtime
    janet_deinit();

    return 0;
}