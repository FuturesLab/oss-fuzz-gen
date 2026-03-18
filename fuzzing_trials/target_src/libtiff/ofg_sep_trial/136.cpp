#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the library for memcpy
#include <tiffio.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Allocate memory using malloc to simulate a TIFF memory allocation
    void *memory = malloc(size > 0 ? size : 1); // Ensure size is not zero

    // Copy the input data to the allocated memory
    if (memory != nullptr && size > 0) {
        memcpy(memory, data, size);
    }

    // Call the function-under-test
    _TIFFfree(memory);

    return 0;
}