#include <stdint.h>
#include <stddef.h>

// Assuming the function is declared in an external library
extern size_t janet_os_rwlock_size();

int LLVMFuzzerTestOneInput_321(const uint8_t *data, size_t size) {
    // Call the function-under-test
    size_t rwlock_size = janet_os_rwlock_size();

    // Use the result to avoid compiler warnings about unused variables
    // This is just to demonstrate that the function is being called
    if (rwlock_size > 0) {
        // Do something trivial with rwlock_size
        volatile size_t dummy = rwlock_size;
        (void)dummy; // Prevent unused variable warning
    }

    return 0;
}