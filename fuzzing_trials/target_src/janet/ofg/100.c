#include <stddef.h>
#include <stdint.h>

// Function-under-test
void *janet_malloc(size_t size);

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid janet_malloc(0) which might return NULL
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test
    void *ptr = janet_malloc(size);

    // Normally, you would use the allocated memory here
    // For fuzzing, we just need to ensure the function is called

    // Free the allocated memory if needed
    // Since we don't have a janet_free function, we assume janet_malloc
    // uses a custom allocator that doesn't require explicit free
    // If janet_malloc uses standard malloc internally, you should free it
    // free(ptr);

    return 0;
}