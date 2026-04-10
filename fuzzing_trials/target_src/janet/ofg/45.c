#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    if (size < sizeof(void*) + sizeof(uint64_t)) {
        return 0;
    }

    // Extract a pointer value from the data
    void *ptr = (void *)(uintptr_t)(data[0]);

    // Extract a uint64_t value from the data
    uint64_t u64_val = *((uint64_t *)(data + sizeof(void*)));

    // Call the function-under-test
    Janet result = janet_nanbox_from_pointer(ptr, u64_val);

    // Use result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}