#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <tiffio.h>
#include <cstring> // Include this for memcpy

extern "C" {
    // Function to test
    void _TIFFfree(void *);
}

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Allocate memory for testing
    void *memory = malloc(size > 0 ? size : 1); // Ensure at least 1 byte is allocated

    if (memory != nullptr) {
        // Copy the data into the allocated memory
        memcpy(memory, data, size);

        // Call the function-under-test
        _TIFFfree(memory);
    }

    return 0;
}