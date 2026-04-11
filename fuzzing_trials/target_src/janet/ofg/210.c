#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // Include this header for malloc
#include <janet.h>

// Remove the redefinition of JanetBuffer
// JanetBuffer is already defined in janet.h

extern void janet_buffer_push_bytes(JanetBuffer *, const uint8_t *, int32_t);

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Initialize a JanetBuffer
    JanetBuffer buffer;
    buffer.data = (uint8_t *)malloc(size);
    buffer.count = 0;
    buffer.capacity = size;

    // Ensure the buffer is not NULL
    if (buffer.data == NULL) {
        return 0;
    }

    // Call the function-under-test
    janet_buffer_push_bytes(&buffer, data, (int32_t)size);

    // Clean up
    free(buffer.data);

    return 0;
}