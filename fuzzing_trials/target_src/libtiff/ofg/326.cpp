#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

extern "C" {
    int _TIFFmemcmp(const void *s1, const void *s2, tmsize_t n);
}

extern "C" int LLVMFuzzerTestOneInput_326(const uint8_t *data, size_t size) {
    // Ensure that the size is at least enough to split into two non-empty parts
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t half_size = size / 2;
    const void *s1 = static_cast<const void *>(data);
    const void *s2 = static_cast<const void *>(data + half_size);

    // Use the smaller half size as the tmsize_t parameter
    tmsize_t n = static_cast<tmsize_t>(half_size);

    // Call the function under test
    int result = _TIFFmemcmp(s1, s2, n);

    // Use the result to prevent the compiler from optimizing the call away
    volatile int prevent_optimization = result;

    return 0;
}