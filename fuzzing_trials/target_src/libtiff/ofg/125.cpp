#include <stdint.h>
#include <stddef.h>

// Include standard libraries first
#include <iostream>
#include <string>

extern "C" {
    // Include project-specific libraries within extern "C"
    #include <tiffio.h>
    #include <tiff.h>
}

// Ensure all functions and code from libtiff are wrapped in extern "C"
extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a TIFFFieldInfo structure
    if (size < sizeof(TIFFFieldInfo)) {
        return 0;
    }

    // Cast the input data to a TIFFFieldInfo pointer
    const TIFFFieldInfo *tiffFieldInfo = reinterpret_cast<const TIFFFieldInfo *>(data);

    // Since TIFFField is an incomplete type, we'll use TIFFFieldInfo for demonstration
    // Call the function-under-test
    int result = TIFFFieldWriteCount(reinterpret_cast<const TIFFField *>(tiffFieldInfo));

    // Use the result to avoid compiler optimizations
    (void)result;

    return 0;
}