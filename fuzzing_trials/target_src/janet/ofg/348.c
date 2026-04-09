#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_348(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize a Janet variable
    Janet result;

    // Call the function-under-test with the provided data
    janet_scan_numeric(data, (int32_t)size, &result);

    return 0;
}