// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_deinit at vm.c:1732:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_getbuffer at janet.c:4519:1 in janet.h
// janet_description_b at janet.c:28645:6 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_buffer_setcount at buffer.c:105:6 in janet.h
// janet_marshal at marsh.c:688:6 in janet.h
// janet_buffer_deinit at buffer.c:74:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static JanetBuffer *create_dummy_buffer(void) {
    JanetBuffer *buffer = (JanetBuffer *)malloc(sizeof(JanetBuffer));
    if (buffer) {
        buffer->gc.flags = 0;
        buffer->count = 0;
        buffer->capacity = 64;
        buffer->data = (uint8_t *)malloc(buffer->capacity);
    }
    return buffer;
}

static void cleanup_buffer(JanetBuffer *buffer) {
    if (buffer) {
        free(buffer->data);
        free(buffer);
    }
}

static JanetTable *create_dummy_table(void) {
    JanetTable *table = (JanetTable *)malloc(sizeof(JanetTable));
    if (table) {
        table->gc.flags = 0;
        table->count = 0;
        table->capacity = 8; // Ensure some capacity
        table->deleted = 0;
        table->data = (JanetKV *)calloc(table->capacity, sizeof(JanetKV));
        table->proto = NULL;
    }
    return table;
}

static void cleanup_table(JanetTable *table) {
    if (table) {
        free(table->data);
        free(table);
    }
}

int LLVMFuzzerTestOneInput_713(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) {
        return 0;
    }

    // Initialize the Janet VM
    janet_init();

    // Create a dummy Janet array with one buffer element
    JanetBuffer *buffer = create_dummy_buffer();
    if (!buffer) {
        janet_deinit();
        return 0;
    }

    // Allocate a Janet array with a size check
    size_t janetArraySize = 2;
    Janet *janetArray = (Janet *)malloc(sizeof(Janet) * janetArraySize);
    if (!janetArray) {
        cleanup_buffer(buffer);
        janet_deinit();
        return 0;
    }

    janetArray[0] = janet_wrap_buffer(buffer);
    janetArray[1] = janet_wrap_nil(); // Ensure a valid Janet object

    // Fuzz janet_getbuffer
    if (janet_checktype(janetArray[0], JANET_BUFFER)) {
        JanetBuffer *resultBuffer = janet_getbuffer(janetArray, 0);

        // Fuzz janet_description_b
        janet_description_b(resultBuffer, janetArray[1]);

        // Fuzz janet_unwrap_buffer
        JanetBuffer *unwrappedBuffer = janet_unwrap_buffer(janetArray[0]);

        // Fuzz janet_buffer_setcount
        int32_t count = (Size > sizeof(Janet) + sizeof(int32_t)) ? *(int32_t *)(Data + sizeof(Janet)) : 0;
        janet_buffer_setcount(resultBuffer, count);

        // Fuzz janet_marshal
        JanetTable *table = create_dummy_table();
        if (table) {
            janet_marshal(resultBuffer, janetArray[1], table, 0);
            cleanup_table(table);
        }

        // Fuzz janet_buffer_deinit
        janet_buffer_deinit(unwrappedBuffer);
    }

    free(janetArray);
    cleanup_buffer(buffer);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}