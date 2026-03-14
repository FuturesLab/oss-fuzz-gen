#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    tjhandle handle;
    int result;

    // Initialize the TurboJPEG decompressor
    handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Since we're fuzzing, let's attempt to decompress the input data
    // For this, we need some dummy variables to pass to the function
    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        // If header decompression is successful, attempt to decompress the image
        unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        if (buffer) {
            tjDecompress2(handle, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);
            free(buffer);
        }
    }

    // Clean up the TurboJPEG decompressor
    result = tjDestroy(handle);

    // Return the result (though for fuzzing purposes, the return value is not typically used)
    return result;
}