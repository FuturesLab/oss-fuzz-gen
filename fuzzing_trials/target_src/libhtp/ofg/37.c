#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Function-under-test declaration
int bstr_util_cmp_mem_nocasenorzero(const void *a, size_t a_len, const void *b, size_t b_len);

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into two non-zero length segments
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t a_len = size / 2;
    size_t b_len = size - a_len;

    const void *a = (const void *)data;
    const void *b = (const void *)(data + a_len);

    // Call the function-under-test
    int result = bstr_util_cmp_mem_nocasenorzero(a, a_len, b, b_len);

    // Use the result to avoid compiler optimizations
    volatile int avoid_optimization = result;

    return 0;
}