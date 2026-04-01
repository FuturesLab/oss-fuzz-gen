#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Allocate memory for the YUV buffer
    // Assuming a maximum image size for fuzzing purposes
    const int maxWidth = 4096;
    const int maxHeight = 4096;
    const int numChannels = 3; // YUV has 3 channels
    unsigned char *yuvBuffer = (unsigned char *)malloc(maxWidth * maxHeight * numChannels);
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Set a width and height for the YUV image
    int width = 128; // Example width
    int height = 128; // Example height

    // Ensure data is not null and has a minimum size
    if (data == nullptr || size < 2) {
        free(yuvBuffer);
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test with valid parameters
    int jpegSubsamp, jpegColorspace;
    unsigned char *nonConstData = const_cast<unsigned char *>(data);
    if (tjDecompressHeader2(handle, nonConstData, size, &width, &height, &jpegSubsamp) == 0) {
        tj3DecompressToYUV8(handle, nonConstData, size, yuvBuffer, 0);
    }

    // Clean up
    free(yuvBuffer);
    tjDestroy(handle);

    return 0;
}