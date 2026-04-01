#include <cstdint>
#include <cstddef>
#include <cstdlib>  // Include the C standard library for malloc and free
#include <tiffio.h>  // Include the TIFF library header

extern "C" {
    void _TIFFmemset(void *, int, tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_342(const uint8_t *data, size_t size) {
    // Ensure the size is large enough for the test
    if (size < sizeof(int) + sizeof(tmsize_t)) {
        return 0;
    }

    // Initialize the parameters for _TIFFmemset
    void *dest = malloc(size);  // Allocate memory for the destination
    if (dest == NULL) {
        return 0;  // Return if memory allocation fails
    }

    // Use the first byte of data to determine the value to set
    int value = static_cast<int>(data[0]);

    // Use the remaining size as the tmsize_t parameter
    tmsize_t length = static_cast<tmsize_t>(size);

    // Call the function-under-test
    _TIFFmemset(dest, value, length);

    // Free the allocated memory
    free(dest);

    return 0;
}