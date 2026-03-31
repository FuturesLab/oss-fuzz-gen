#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern int64_t bstr_util_mem_to_pint(const void *mem, size_t size, int base, size_t *processed);

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for testing
    if (size < sizeof(size_t) + sizeof(int)) {
        return 0;
    }

    // Initialize the parameters for bstr_util_mem_to_pint
    const void *mem = (const void *)data;
    size_t processed = 0;

    // Extract base from data, ensuring it is a valid base (2 to 36)
    int base = (int)(data[size - 1] % 35) + 2;

    // Call the function-under-test
    int64_t result = bstr_util_mem_to_pint(mem, size - sizeof(size_t) - sizeof(int), base, &processed);

    // Use the result and processed to avoid compiler optimizations
    (void)result;
    (void)processed;

    return 0;
}