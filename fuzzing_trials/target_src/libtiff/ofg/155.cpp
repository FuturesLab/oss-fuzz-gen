#include <cstdint>
#include <cstdlib>
#include <tiffio.h>  // Ensure libtiff is installed and this header is available.

extern "C" {
    void* _TIFFmalloc(tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Initialize tmsize_t variable with a non-zero value.
    tmsize_t tiff_size = static_cast<tmsize_t>(size > 0 ? size : 1);

    // Call the function-under-test.
    void* allocated_memory = _TIFFmalloc(tiff_size);

    // If memory was successfully allocated, free it.
    if (allocated_memory != nullptr) {
        _TIFFfree(allocated_memory);
    }

    return 0;
}