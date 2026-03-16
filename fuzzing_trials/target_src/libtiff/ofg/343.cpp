#include <cstdint>
#include <cstdlib>
#include <tiffio.h>  // Include the TIFF library headers

extern "C" {
    // Function signature from the TIFF library
    void _TIFFmemset(void *s, int c, tmsize_t n);
}

extern "C" int LLVMFuzzerTestOneInput_343(const uint8_t *data, size_t size) {
    // Ensure there is enough data to use for the function parameters
    if (size < sizeof(int) + sizeof(tmsize_t)) {
        return 0;
    }

    // Allocate memory for the buffer to be set
    tmsize_t bufferSize = static_cast<tmsize_t>(size);
    void *buffer = malloc(bufferSize);
    if (buffer == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Extract an int value from the data
    int c = static_cast<int>(data[0]);

    // Call the function-under-test
    _TIFFmemset(buffer, c, bufferSize);

    // Free the allocated memory
    free(buffer);

    return 0;
}