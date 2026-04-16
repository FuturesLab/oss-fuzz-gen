#include <stdint.h>
#include <stddef.h>

// Forward declaration of the function-under-test
size_t janet_os_mutex_size();

int LLVMFuzzerTestOneInput_381(const uint8_t *data, size_t size) {
    // Call the function-under-test
    size_t mutex_size = janet_os_mutex_size();

    // Use the result in some way to avoid compiler optimizations
    if (mutex_size == 0) {
        return 0;
    }

    return 0;
}