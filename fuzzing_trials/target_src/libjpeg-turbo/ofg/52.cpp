#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, return early
    }

    // Define variables for image dimensions and subsampling
    int width = 0, height = 0, jpegSubsamp = 0;

    // Get the image dimensions and subsampling type from the JPEG header
    if (tjDecompressHeader2(handle, const_cast<uint8_t *>(data), size, &width, &height, &jpegSubsamp) != 0) {
        tjDestroy(handle);
        return 0; // If header decompression fails, return early
    }

    // Allocate memory for YUV planes
    unsigned char *yuvPlanes[3];
    int strides[3];
    for (int i = 0; i < 3; i++) {
        strides[i] = 0; // Initialize strides to zero
        yuvPlanes[i] = static_cast<unsigned char *>(malloc(tjPlaneSizeYUV(i, width, strides[i], height, jpegSubsamp)));
        if (yuvPlanes[i] == nullptr) {
            // Free allocated memory and destroy handle on failure
            for (int j = 0; j < i; j++) {
                free(yuvPlanes[j]);
            }
            tjDestroy(handle);
            return 0;
        }
    }

    // Decompress the JPEG image to YUV planes
    tjDecompressToYUVPlanes(handle, const_cast<uint8_t *>(data), size, yuvPlanes, width, strides, height, 0);

    // Free allocated memory
    for (int i = 0; i < 3; i++) {
        free(yuvPlanes[i]);
    }

    // Destroy the TurboJPEG decompressor handle
    tjDestroy(handle);

    return 0;
}