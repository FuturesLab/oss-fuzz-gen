#include <stdint.h>
#include <stddef.h>

// Assuming the function is declared like this, as the actual implementation is not provided
int janet_scan_int64(const uint8_t *input, int32_t len, int64_t *output);

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to avoid undefined behavior
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Initialize the output variable
    int64_t output = 0;

    // Call the function-under-test
    janet_scan_int64(data, (int32_t)size, &output);

    return 0;
}