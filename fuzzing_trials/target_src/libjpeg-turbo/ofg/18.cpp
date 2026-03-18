#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Ensure there's enough data for width and height
    }

    // Initialize the TurboJPEG compressor
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    // Extract width and height from the input data
    int width = data[0] + 1; // Avoid zero width
    int height = data[1] + 1; // Avoid zero height

    // Ensure the input buffer is large enough for the image data
    if (size < static_cast<size_t>(width * height * 3 + 4)) {
        tjDestroy(handle);
        return 0;
    }

    // Set up the input image buffer
    const unsigned char *srcBuf = data + 4;

    // Allocate the output buffer
    unsigned char *dstBuf = (unsigned char *)malloc(width * height);
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Set the padding and subsampling options
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB; // Set a valid pixel format
    int subsamp = TJSAMP_444; // Use a valid subsampling option
    int flags = 0; // No special flags

    // Call the function-under-test with correct number of arguments
    tjEncodeYUV3(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, 4, subsamp, flags);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}