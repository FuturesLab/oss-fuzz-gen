#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the cstring library for std::memcpy
#include <tiffio.h> // Ensure that the libtiff library is included for _TIFFmalloc

extern "C" {
    #include <tiffio.h> // Wrap the C library includes in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Define a tmsize_t variable and initialize it using the input data
    tmsize_t tmsize = 0;

    // Ensure the size is large enough to extract a tmsize_t value
    if (size >= sizeof(tmsize_t)) {
        // Copy the first sizeof(tmsize_t) bytes from data to tmsize
        std::memcpy(&tmsize, data, sizeof(tmsize_t));

        // Call the function-under-test with the tmsize
        void *result = _TIFFmalloc(tmsize);

        // If the allocation was successful, free the allocated memory
        if (result != nullptr) {
            _TIFFfree(result);
        }
    }

    return 0;
}