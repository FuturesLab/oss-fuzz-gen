#include <cstdint>
#include <cstddef>
#include <tiffio.h>  // Ensure that libtiff is installed and properly linked

extern "C" int LLVMFuzzerTestOneInput_343(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to perform meaningful operations
    if (size < 1) {
        return 0;
    }

    // Allocate a buffer of the same size as the input data
    void *buffer = _TIFFmalloc(size);
    if (buffer == nullptr) {
        return 0;
    }

    // Use the first byte of data as the value to set in the memory
    int value = static_cast<int>(data[0]);

    // Call the function-under-test
    _TIFFmemset(buffer, value, static_cast<tmsize_t>(size));

    // Free the allocated memory
    _TIFFfree(buffer);

    return 0;
}