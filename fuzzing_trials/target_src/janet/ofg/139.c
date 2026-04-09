#include <stdint.h>
#include <stddef.h>

// Assume the janet_scan_int64 function is defined elsewhere
int janet_scan_int64(const uint8_t *data, int32_t len, int64_t *out);

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to perform the operation
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Initialize the output variable
    int64_t output = 0;

    // Call the function-under-test
    janet_scan_int64(data, (int32_t)size, &output);

    return 0;
}