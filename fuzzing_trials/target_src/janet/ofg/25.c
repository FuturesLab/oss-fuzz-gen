#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

extern void janet_to_string_b(JanetBuffer *, Janet);

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0; // Not enough data to form a Janet object
    }

    // Initialize a JanetBuffer
    JanetBuffer buffer;
    janet_buffer_init(&buffer, 10);

    // Use the data to create a Janet object
    Janet janet_obj = janet_wrap_number(*(double *)data);

    // Call the function-under-test
    janet_to_string_b(&buffer, janet_obj);

    // Clean up
    janet_buffer_deinit(&buffer);

    return 0;
}