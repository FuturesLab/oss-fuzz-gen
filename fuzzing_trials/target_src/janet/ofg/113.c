#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Use the first part of the data as a pointer (void*)
    const void *ptr = (const void *)(data);

    // Use the next part of the data as a uint64_t value
    uint64_t u64_value;
    memcpy(&u64_value, data, sizeof(uint64_t));

    // Call the function-under-test
    Janet result = janet_nanbox_from_cpointer(ptr, u64_value);

    // Use the result in some way to avoid compiler optimizations that might remove the call
    (void)result;

    return 0;
}