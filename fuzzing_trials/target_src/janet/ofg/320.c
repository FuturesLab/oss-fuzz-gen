#include <stdint.h>
#include <stddef.h>

// Assuming the function is declared in a header file related to the library
size_t janet_os_rwlock_size();

int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    // Call the function-under-test
    size_t rwlock_size = janet_os_rwlock_size();

    // Optionally, you can use the result in some way to ensure the call is made
    // For example, just to avoid unused variable warning
    if (rwlock_size > 0) {
        // Do something trivial
        rwlock_size = rwlock_size;
    }

    return 0;
}