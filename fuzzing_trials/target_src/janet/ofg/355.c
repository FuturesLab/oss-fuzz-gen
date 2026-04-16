#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Ensure Janet is initialized before using any Janet functions
__attribute__((constructor))
static void janet_initialize() {
    janet_init();
}

int LLVMFuzzerTestOneInput_355(const uint8_t *data, size_t size) {
    JanetBuffer buffer;
    janet_buffer_init(&buffer, size);

    // Copy the input data to the buffer
    if (size > 0) {
        janet_buffer_push_bytes(&buffer, data, size);
    }

    // Call the function-under-test
    janet_buffer_deinit(&buffer);

    return 0;
}