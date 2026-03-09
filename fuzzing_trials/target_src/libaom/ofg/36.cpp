#include <cstdint>
#include <cstdlib>
#include <cstddef>

extern "C" {
    // Assuming the function is declared in a header file, include it here.
    // #include "aom_uleb_decode.h"
    int aom_uleb_decode(const uint8_t *, size_t, uint64_t *, size_t *);
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize variables to be used as parameters for the function-under-test
    uint64_t decoded_value = 0;
    size_t decoded_size = 0;

    // Call the function-under-test with the initialized parameters
    int result = aom_uleb_decode(data, size, &decoded_value, &decoded_size);

    // The result can be used for further checks if needed, but is not necessary for the fuzzing harness
    (void)result; // Suppress unused variable warning

    return 0;
}