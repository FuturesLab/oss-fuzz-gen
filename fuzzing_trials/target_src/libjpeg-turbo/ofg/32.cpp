#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Define and initialize the parameters for tjLoadImage
    const char *filename = "dummy.jpg"; // Use a dummy filename
    int width = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB; // Common pixel format
    int align = 1; // Common alignment
    int flags = 0; // No specific flags

    // Allocate memory for the output image
    unsigned char *imageBuffer = nullptr;

    // Call the function-under-test
    imageBuffer = tjLoadImage(filename, &width, align, &height, &pixelFormat, flags);

    // Free the allocated image buffer if it's not nullptr
    if (imageBuffer != nullptr) {
        tjFree(imageBuffer);
    }

    return 0;
}