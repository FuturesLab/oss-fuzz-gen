#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern int bstr_util_cmp_mem_nocasenorzero(const void *s1, size_t n1, const void *s2, size_t n2);

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into two non-zero segments
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t n1 = size / 2;
    size_t n2 = size - n1;

    // Ensure both parts are non-zero in size
    if (n1 == 0 || n2 == 0) {
        return 0;
    }

    const void *s1 = (const void *)data;
    const void *s2 = (const void *)(data + n1);

    // Call the function-under-test
    int result = bstr_util_cmp_mem_nocasenorzero(s1, n1, s2, n2);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}