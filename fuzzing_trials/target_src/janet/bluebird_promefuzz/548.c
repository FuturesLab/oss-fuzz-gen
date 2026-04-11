#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static void initialize_fiber(JanetFiber *fiber) {
    if (fiber) {
        fiber->flags = 0;
        fiber->frame = 0;
        fiber->stackstart = 0;
        fiber->stacktop = 0;
        fiber->capacity = 1024;
        fiber->maxstack = 2048;
        fiber->env = janet_table(0); // Properly initialize the environment
        fiber->data = NULL;
        fiber->child = NULL;
        fiber->last_value.u64 = 0;
#ifdef JANET_EV
        fiber->sched_id = 0;
        fiber->ev_callback = NULL;
        fiber->ev_stream = NULL;
        fiber->ev_state = NULL;
        fiber->supervisor_channel = NULL;
#endif
    }
}

static void initialize_stream(JanetStream *stream) {
    if (stream) {
        stream->handle = 0;
        stream->flags = 0;
        stream->index = 0;
        stream->read_fiber = NULL;
        stream->write_fiber = NULL;
        stream->methods = NULL;
    }
}

int LLVMFuzzerTestOneInput_548(const uint8_t *Data, size_t Size) {
    (void)Data; // Unused parameter
    (void)Size; // Unused parameter

    // Initialize the Janet runtime
    janet_init();

    JanetFiber fiber;
    initialize_fiber(&fiber);

    JanetStream stream;
    initialize_stream(&stream);

    fiber.ev_stream = &stream;

    // Fuzz janet_async_end
    janet_async_end(&fiber);

    // Fuzz janet_schedule
    Janet value;
    value.u64 = 0;
    janet_schedule(&fiber, value);

    // Fuzz janet_current_fiber
    JanetFiber *current_fiber = janet_current_fiber();
    if (current_fiber) {
        janet_async_end(current_fiber);
    }

    // Fuzz janet_async_in_flight
    janet_async_in_flight(&fiber);

    // Fuzz janet_loop1
    JanetFiber *loop_fiber = janet_loop1();
    if (loop_fiber) {
        janet_async_end(loop_fiber);
    }

    // Fuzz janet_root_fiber
    JanetFiber *root_fiber = janet_root_fiber();
    if (root_fiber) {
        janet_async_end(root_fiber);
    }

    // Cleanup the Janet runtime
    janet_deinit();

    return 0;
}