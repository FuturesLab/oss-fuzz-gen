#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Include the function-under-test signature
    int _TIFFmemcmp(const void *, const void *, tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_325(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into two non-null pointers
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t half_size = size / 2;
    const void *ptr1 = static_cast<const void *>(data);
    const void *ptr2 = static_cast<const void *>(data + half_size);

    // Use the smaller of the half size or remaining size to ensure valid tmsize_t
    tmsize_t compare_size = static_cast<tmsize_t>(half_size);

    // Call the function-under-test
    _TIFFmemcmp(ptr1, ptr2, compare_size);

    return 0;
}