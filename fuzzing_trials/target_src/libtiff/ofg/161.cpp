#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Ensure size is not zero to prevent undefined behavior in _TIFFmalloc
    if (size == 0) {
        return 0;
    }

    // Use the size from the fuzzer input as the tmsize_t parameter
    tmsize_t tiff_size = static_cast<tmsize_t>(size);

    // Call the function-under-test
    void *allocated_memory = _TIFFmalloc(tiff_size);

    // If memory allocation was successful, free the allocated memory
    if (allocated_memory != NULL) {
        _TIFFfree(allocated_memory);
    }

    return 0;
}