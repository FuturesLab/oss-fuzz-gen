#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include the C++ header for memcpy

extern "C" {
    void TIFFRGBAImageEnd(TIFFRGBAImage *);
}

extern "C" int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFRGBAImage)) {
        return 0; // Not enough data to initialize TIFFRGBAImage
    }

    // Initialize a TIFFRGBAImage structure from the input data
    TIFFRGBAImage img;
    std::memcpy(&img, data, sizeof(TIFFRGBAImage)); // Use std::memcpy for C++

    // Call the function-under-test
    TIFFRGBAImageEnd(&img);

    return 0;
}