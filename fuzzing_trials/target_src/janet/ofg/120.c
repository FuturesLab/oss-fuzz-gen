#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Fuzzing harness
int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Call the function-under-test
    Janet result = janet_wrap_true();

    // Use the result in some way to avoid compiler optimizations removing the call
    if (janet_truthy(result)) {
        // Do something trivial with the result
        volatile int dummy = 1;
        (void)dummy;
    }

    return 0;
}