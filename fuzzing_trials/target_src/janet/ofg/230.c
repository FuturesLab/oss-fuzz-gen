#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memset

// Function signature provided for fuzzing
void *janet_smalloc(size_t size);

// Fuzzing harness for the janet_smalloc function
int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid passing 0 to janet_smalloc
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test with the size derived from the input
    void *allocated_memory = janet_smalloc(size);

    // Use the allocated memory if it's not NULL
    if (allocated_memory != NULL) {
        // Write to the allocated memory to increase code coverage
        // For simplicity, use memset to fill the memory with data
        memset(allocated_memory, 0xAA, size);

        // Assuming there's a corresponding free function, e.g., janet_sfree
        // Uncomment the line below if such a function exists
        // janet_sfree(allocated_memory);
    }

    return 0;
}