#include <cstdint>
#include <cstddef>
#include <cstring>
#include <tiffio.h>

extern "C" {
    // Declare the function-under-test
    int _TIFFmemcmp(const void *s1, const void *s2, tmsize_t n);
}

extern "C" int LLVMFuzzerTestOneInput_324(const uint8_t *data, size_t size) {
    // Ensure there is enough data to perform a meaningful comparison
    if (size < 2) {
        return 0;
    }

    // Split the data into two parts for comparison
    size_t half_size = size / 2;
    const void *ptr1 = static_cast<const void *>(data);
    const void *ptr2 = static_cast<const void *>(data + half_size);

    // Ensure the comparison size does not exceed the available data
    tmsize_t compare_size = static_cast<tmsize_t>(half_size);

    // Call the function-under-test
    int result = _TIFFmemcmp(ptr1, ptr2, compare_size);

    // Use the result in some way to avoid compiler optimizations
    volatile int use_result = result;

    return 0;
}