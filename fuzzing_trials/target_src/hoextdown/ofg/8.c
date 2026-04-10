#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
int hoedown_autolink_is_safe(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Call the function-under-test with the provided data and size
    hoedown_autolink_is_safe(data, size);

    return 0;
}