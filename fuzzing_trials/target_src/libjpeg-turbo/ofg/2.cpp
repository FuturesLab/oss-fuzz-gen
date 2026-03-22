#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Initialize variables for tjCompress
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Ensure the input size is large enough for a basic image
    int width = 64;
    int height = 64;
    int pixelFormat = TJPF_RGB;
    int padding = 1; // Default padding
    int subsamp = TJSAMP_444; // No subsampling
    int quality = 75; // Typical quality level

    // Allocate output buffer
    unsigned long jpegSize = tjBufSize(width, height, subsamp);
    unsigned char *jpegBuf = (unsigned char *)tjAlloc(jpegSize);

    // Check if jpegBuf allocation was successful
    if (!jpegBuf) {
        tjDestroy(handle);
        return 0;
    }

    // Call tjCompress
    int result = tjCompress2(
        handle,
        const_cast<unsigned char *>(data), // Source image buffer
        width,
        0, // pitch (0 for default)
        height,
        pixelFormat,
        &jpegBuf,
        &jpegSize,
        subsamp,
        quality,
        TJFLAG_FASTDCT
    );

    // Clean up
    tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}