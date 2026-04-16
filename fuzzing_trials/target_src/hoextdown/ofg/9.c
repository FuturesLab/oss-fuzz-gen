#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
int hoedown_autolink_is_safe(const uint8_t *data, size_t size);

// Fuzzing harness
int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Call the function-under-test with the provided data and size
    int result = hoedown_autolink_is_safe(data, size);

    // Return 0 to indicate the fuzzer should continue testing
    return 0;
}