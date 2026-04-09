#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Fuzzing harness
int LLVMFuzzerTestOneInput_369(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a non-NULL pointer
    if (size < sizeof(void *)) {
        return 0;
    }

    // Create a non-NULL pointer from the input data
    void *ptr = (void *)data;

    // Call the function-under-test
    Janet result = janet_wrap_pointer(ptr);

    // Use the result to avoid compiler optimizations removing the call
    if (janet_checktype(result, JANET_NIL)) {
        // Do something with the result if needed
    }

    return 0;
}