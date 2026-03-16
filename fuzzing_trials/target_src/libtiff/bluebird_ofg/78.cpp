#include "cstdint"
#include <cstddef>
#include "cstring"
#include "tiffio.h"

extern "C" {
    int _TIFFmemcmp(const void *s1, const void *s2, tmsize_t n);
}

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Ensure there is enough data to perform a meaningful comparison
    if (size < 2) {
        return 0;
    }

    // Split the data into two parts for comparison
    size_t half_size = size / 2;
    const void *ptr1 = static_cast<const void*>(data);
    const void *ptr2 = static_cast<const void*>(data + half_size);

    // Use the smaller half size for comparison
    tmsize_t compare_size = static_cast<tmsize_t>(half_size);

    // Call the function under test
    int result = _TIFFmemcmp(ptr1, ptr2, compare_size);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile int use_result = result;
    (void)use_result;

    return 0;
}