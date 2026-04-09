#include <stddef.h>
#include <stdint.h>

// Assuming the function janet_gclock is defined elsewhere
int janet_gclock();

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int result = janet_gclock();

    // Return 0 to indicate the fuzzer can continue
    return 0;
}