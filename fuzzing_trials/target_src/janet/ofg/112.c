#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function prototype for the function under test
Janet janet_nanbox_from_cpointer(const void *ptr, uint64_t num);

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a uint64_t
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Extract a pointer from the data
    const void *ptr = (const void *)(data);

    // Extract a uint64_t value from the data
    uint64_t num = *((uint64_t *)(data));

    // Call the function-under-test
    Janet result = janet_nanbox_from_cpointer(ptr, num);

    // Use the result in some way to prevent compiler optimizations
    (void)result;

    return 0;
}