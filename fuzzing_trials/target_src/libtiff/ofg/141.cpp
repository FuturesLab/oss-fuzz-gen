#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Allocate memory based on the input size
    void *ptr = malloc(size > 0 ? size : 1); // Ensure size is not zero to avoid malloc(0)

    // Ensure the pointer is non-NULL
    if (ptr == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Optionally, copy data into the allocated memory
    if (size > 0) {
        memcpy(ptr, data, size);
    }

    // Call the function-under-test
    _TIFFfree(ptr);

    return 0;
}