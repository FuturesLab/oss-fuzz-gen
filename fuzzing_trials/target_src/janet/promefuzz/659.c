// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_buffer_init at buffer.c:54:14 in janet.h
// janet_ev_read at janet.c:11509:22 in janet.h
// janet_ev_recvfrom at janet.c:11522:22 in janet.h
// janet_ev_recvchunk at janet.c:11519:22 in janet.h
// janet_ev_send_buffer at janet.c:11755:22 in janet.h
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

static JanetBuffer *create_buffer(int32_t capacity) {
    JanetBuffer *buffer = (JanetBuffer *)malloc(sizeof(JanetBuffer));
    if (buffer) {
        janet_buffer_init(buffer, capacity);
    }
    return buffer;
}

static JanetStream *create_stream() {
    JanetStream *stream = (JanetStream *)malloc(sizeof(JanetStream));
    if (stream) {
        memset(stream, 0, sizeof(JanetStream));
    }
    return stream;
}

int LLVMFuzzerTestOneInput_659(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    int32_t capacity = *(int32_t *)Data;
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    JanetBuffer *buffer = create_buffer(capacity);
    if (!buffer) return 0;

    JanetStream *stream = create_stream();
    if (!stream) {
        free(buffer);
        return 0;
    }

    if (Size >= sizeof(int32_t)) {
        int32_t nbytes = *(int32_t *)Data;
        janet_ev_read(stream, buffer, nbytes);
        Data += sizeof(int32_t);
        Size -= sizeof(int32_t);

        if (Size >= sizeof(int)) {
            int flags = *(int *)Data;
            janet_ev_recvfrom(stream, buffer, nbytes, flags);
            janet_ev_recvchunk(stream, buffer, nbytes, flags);
            janet_ev_send_buffer(stream, buffer, flags);
        }
    }

    janet_buffer_setcount(buffer, capacity);

    free(stream);
    free(buffer);
    return 0;
}