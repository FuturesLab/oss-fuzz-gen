#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Call the function-under-test
    JanetRNG *rng = janet_default_rng();

    // Use the rng in some way to ensure it is not optimized away
    if (rng != NULL) {
        // For example, generate a random number
        uint32_t random_number = janet_rng_u32(rng);
        
        // Optionally, use the random number in some dummy operation
        if (random_number == 0) {
            return 0;
        }
    }

    return 0;
}