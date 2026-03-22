#include <stdint.h>
#include <stddef.h>
#include <cstdlib> // For std::malloc and std::free

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // Failed to initialize, exit early
    }

    // Define variables for decompression
    int width, height, jpegSubsamp, jpegColorspace;

    // Attempt to read the header to get image dimensions
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0; // Failed to read header, exit early
    }

    // Allocate buffer for decompressed image
    uint16_t *outputBuffer = (uint16_t *)std::malloc(width * height * 3 * sizeof(uint16_t)); // Assuming RGB format
    if (outputBuffer == nullptr) {
        tjDestroy(handle);
        return 0; // Failed to allocate memory, exit early
    }

    // Call the function-under-test with the correct number of arguments
    if (tj3Decompress16(handle, data, size, outputBuffer, width * 3 * sizeof(uint16_t), TJPF_RGB) != 0) {
        // Handle decompression error
    }

    // Clean up
    std::free(outputBuffer);
    tjDestroy(handle);

    return 0;
}