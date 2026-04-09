#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Assume the function is declared in a header file included in the project
size_t janet_os_mutex_size();

int LLVMFuzzerTestOneInput_1492(const uint8_t *data, size_t size) {
    // Call the function-under-test
    size_t mutex_size = janet_os_mutex_size();

    // Use the returned size in some way to prevent compiler optimizations
    // from removing the call. This is a common technique in fuzzing harnesses.
    // Here, we simulate a scenario where the return value affects behavior.
    if (mutex_size > 0 && size > 0) {
        // Use the data and the mutex_size in some hypothetical operation
        size_t index = data[0] % mutex_size;
        printf("Index: %zu\n", index); // Use the index to simulate some operation
    } else {
        return 0;
    }

    return 0;
}