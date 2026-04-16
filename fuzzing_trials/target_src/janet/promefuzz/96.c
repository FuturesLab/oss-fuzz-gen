// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_fiber at fiber.c:96:13 in janet.h
// janet_fiber at fiber.c:96:13 in janet.h
// janet_ev_sendto_string at janet.c:11767:22 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_panics at janet.c:4435:6 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_formatc at janet.c:29440:16 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static JanetFunction dummy_function = {0}; // Define a dummy JanetFunction

static void fuzz_janet_ev_sendto_string(JanetStream *stream, const uint8_t *data, size_t size) {
    if (size < 1) return; // Ensure there's at least some data
    JanetString str = janet_string(data, (int32_t)size);

    // Properly initialize the stream
    stream->handle = -1;
    stream->flags = 0;
    stream->index = 0;
    
    // Initialize fibers with dummy arguments and a valid function
    Janet dummy_args[1] = { { .u64 = 0 } };
    stream->read_fiber = janet_fiber(&dummy_function, 0, 0, dummy_args);
    stream->write_fiber = janet_fiber(&dummy_function, 0, 0, dummy_args);
    stream->methods = NULL;

    // Use a valid destination and flags
    int dummy_dest = 0;
    janet_ev_sendto_string(stream, str, &dummy_dest, 0);
}

static void fuzz_janet_panics(const uint8_t *data, size_t size) {
    if (size < 1) return; // Ensure there's at least some data
    JanetString str = janet_string(data, (int32_t)size);
    janet_panics(str);
}

static void fuzz_janet_unwrap_string(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, data, sizeof(Janet));
    janet_unwrap_string(x);
}

static void fuzz_janet_string(const uint8_t *data, size_t size) {
    if (size < 1) return; // Ensure there's at least some data
    janet_string(data, (int32_t)size);
}

static void fuzz_janet_formatc(const uint8_t *data, size_t size) {
    if (size < 1) return; // Ensure there's at least some data
    char format[64];
    snprintf(format, sizeof(format), "%.*s", (int)size, data);
    janet_formatc(format);
}

int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    initialize_janet();

    JanetStream stream;
    memset(&stream, 0, sizeof(JanetStream));

    fuzz_janet_ev_sendto_string(&stream, Data, Size);
    fuzz_janet_panics(Data, Size);
    fuzz_janet_unwrap_string(Data, Size);
    fuzz_janet_string(Data, Size);
    fuzz_janet_formatc(Data, Size);

    return 0;
}