#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    // Ensure size is large enough for necessary parameters
    if (size < 6) {
        tjDestroy(handle);
        return 0;
    }

    // Set up input parameters
    const unsigned char *srcBuf = data;
    int pad = 4; // Typical padding value for YUV images
    int width = 64; // Arbitrary width for testing
    int height = 64; // Arbitrary height for testing
    int flags = 0; // No specific flags

    // Allocate memory for the destination buffer
    unsigned char *dstBuf = static_cast<unsigned char *>(malloc(width * height * 3));
    if (!dstBuf) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    // Ensure the input data is not null and has a minimum size
    if (size >= width * height * 3) {
        // Attempt to decompress the JPEG image from the input data
        int jpegSubsamp, jpegColorspace;
        if (tjDecompressHeader3(handle, srcBuf, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
            int result = tjDecompress2(handle, srcBuf, size, dstBuf, width, 0 /* pitch */, height, TJPF_RGB, flags);
            (void)result; // Suppress unused variable warning
        }
    }

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}