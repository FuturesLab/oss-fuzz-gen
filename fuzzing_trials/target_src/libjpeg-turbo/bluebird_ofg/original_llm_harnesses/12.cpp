#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Initialize TurboJPEG compressor
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    // Define parameters for tjCompress2
    const unsigned char *srcBuf = data;  // Source buffer is the input data
    int width = 100;                     // Arbitrary width
    int height = 100;                    // Arbitrary height
    int pixelFormat = TJPF_RGB;          // Pixel format
    int pitch = 0;                       // Pitch (0 means use width)
    unsigned char *jpegBuf = nullptr;    // Destination buffer (will be allocated by TurboJPEG)
    unsigned long jpegSize = 0;          // Size of the compressed JPEG image
    int jpegSubsamp = TJSAMP_444;        // Subsampling option
    int jpegQual = 75;                   // JPEG quality
    int flags = 0;                       // Compression flags

    // Call the function-under-test
    tjCompress2(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags);

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}