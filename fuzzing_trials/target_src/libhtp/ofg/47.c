#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Function-under-test declaration
int bstr_util_cmp_mem(const void *mem1, size_t len1, const void *mem2, size_t len2);

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Split the input data into two parts for comparison
    size_t half_size = size / 2;

    // Define two memory blocks for comparison
    const void *mem1 = data;
    size_t len1 = half_size;

    const void *mem2 = data + half_size;
    size_t len2 = size - half_size;

    // Ensure that both memory blocks are non-NULL and have non-zero length
    if (len1 > 0 && len2 > 0) {
        // Call the function-under-test
        bstr_util_cmp_mem(mem1, len1, mem2, len2);
    }

    return 0;
}