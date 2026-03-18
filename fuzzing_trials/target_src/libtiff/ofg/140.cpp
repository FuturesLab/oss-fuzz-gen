#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include the header for memcpy
#include <tiffio.h>

extern "C" {
    // Function declaration for _TIFFfree
    void _TIFFfree(void *);
}

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Allocate memory using malloc
    void *ptr = malloc(size);

    // Ensure ptr is not NULL and data is not empty
    if (ptr != nullptr && size > 0) {
        // Copy data into allocated memory
        memcpy(ptr, data, size);

        // Call the function-under-test
        _TIFFfree(ptr);
    } else {
        // If allocation failed or size is zero, free the pointer
        free(ptr);
    }

    return 0;
}