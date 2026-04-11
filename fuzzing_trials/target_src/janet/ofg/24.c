#include <janet.h>
#include <stdint.h>
#include <stddef.h>

// Fuzzing harness for janet_unwrap_cfunction
int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Call the function-under-test
    JanetCFunction cfunc = janet_unwrap_cfunction(janet_obj);

    // Use the result (cfunc) in some way to avoid compiler optimizations
    // For fuzzing purposes, we don't need to do anything specific with cfunc

    return 0;
}