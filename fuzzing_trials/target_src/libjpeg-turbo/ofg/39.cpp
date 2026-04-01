extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG decompressor
    tjhandle decompressor = tjInitDecompress();
    if (decompressor == nullptr) {
        return 0;
    }

    // Set up parameters for the function call
    unsigned long jpegSize = static_cast<unsigned long>(size);
    int width = 128;  // Example width, adjust as needed
    int height = 128; // Example height, adjust as needed
    int subsamp, colorspace;

    // Allocate memory for YUV planes
    unsigned char *yuvPlanes[3];
    int strides[3] = { width, width / 2, width / 2 }; // Assuming 4:2:0 subsampling
    for (int i = 0; i < 3; i++) {
        yuvPlanes[i] = static_cast<unsigned char *>(malloc(strides[i] * height / (i == 0 ? 1 : 2)));
        if (yuvPlanes[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                free(yuvPlanes[j]);
            }
            tjDestroy(decompressor);
            return 0;
        }
    }

    // Call the function-under-test
    int result = tjDecompressToYUVPlanes(decompressor, data, jpegSize, yuvPlanes, width, strides, height, 0);

    // Clean up
    for (int i = 0; i < 3; i++) {
        free(yuvPlanes[i]);
    }
    tjDestroy(decompressor);

    return result;
}