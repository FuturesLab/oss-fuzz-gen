#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Function declaration for the function-under-test
    void* _TIFFrealloc(void *ptr, tmsize_t size);
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize variables
    void *ptr = nullptr;
    tmsize_t newSize = 0;

    // Ensure size is non-zero to avoid reallocating to zero size
    if (size > 0) {
        // Use the first byte of data to determine the new size
        newSize = static_cast<tmsize_t>(data[0]);

        // Allocate initial memory block
        ptr = malloc(size);
        if (ptr == nullptr) {
            return 0; // Exit if memory allocation fails
        }

        // Call the function-under-test
        void *newPtr = _TIFFrealloc(ptr, newSize);

        // Free the newly allocated memory if successful
        if (newPtr != nullptr) {
            free(newPtr);
        }
    }

    return 0;
}