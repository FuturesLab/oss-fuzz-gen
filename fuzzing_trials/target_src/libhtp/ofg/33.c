#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

// Function-under-test
int64_t bstr_util_mem_to_pint(const void *mem, size_t len, int base, size_t *processed);

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for testing
    if (size < sizeof(int) + sizeof(size_t)) {
        return 0;
    }

    // Extract base and processed size from the data
    int base = *((int *)data);
    size_t processed = 0;

    // Adjust the pointer to skip the extracted base
    const void *mem = data + sizeof(int);

    // Adjust the length to account for the extracted base
    size_t len = size - sizeof(int);

    // Call the function-under-test
    int64_t result = bstr_util_mem_to_pint(mem, len, base, &processed);

    // Use the result and processed in some way to avoid unused variable warnings
    (void)result;
    (void)processed;

    return 0;
}