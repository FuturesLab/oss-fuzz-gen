#include <stdint.h>
#include <stddef.h>
#include "janet.h"  // Assuming this is the header file where the function is declared

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for extracting a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Use a portion of the data as a pointer
    void *ptr = (void *)data;

    // Extract a uint64_t value from the data
    uint64_t num = *(uint64_t *)(data);

    // Call the function-under-test
    Janet result = janet_nanbox_from_pointer(ptr, num);

    // The result can be used for further operations if needed
    // For now, we simply return 0 to indicate the fuzzer should continue
    return 0;
}