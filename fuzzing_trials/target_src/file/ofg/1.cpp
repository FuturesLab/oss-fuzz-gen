#include <cstdint>
#include <cstdlib>

extern "C" {
    // Declare the function-under-test
    int magic_version();
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version = magic_version();

    // Optionally, use the result in some way or log it
    // For fuzzing purposes, we just call the function to ensure it executes
    (void)version; // Suppress unused variable warning

    return 0;
}