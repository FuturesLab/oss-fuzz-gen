#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    if (size < 3) return 0; // Ensure there's enough data for width, height, and at least one pixel

    // Initialize variables for the function-under-test
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Extract width and height from input data to simulate variable dimensions
    int width = data[0] % 256 + 1; // Ensure width is at least 1
    int height = data[1] % 256 + 1; // Ensure height is at least 1
    int pitch = width * tjPixelSize[TJPF_RGB]; // Example pitch for RGB format

    // Use input data to determine subsampling
    int subsamp = data[2] % 5; // TJSAMP_444, TJSAMP_422, TJSAMP_420, TJSAMP_GRAY, TJSAMP_440

    // Calculate the minimum required size for the image data
    int minSize = width * height * tjPixelSize[TJPF_RGB];
    if (size < minSize + 3) {
        tjDestroy(handle);
        return 0;
    }

    const unsigned char *srcBuf = data + 3; // Source buffer from input data, offset by 3 for width, height, and subsamp

    // Allocate memory for destination planes based on subsampling
    unsigned char *dstPlanes[3] = {nullptr, nullptr, nullptr};
    int planeSizes[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        planeSizes[i] = tj3YUVPlaneSize(i, width, 0, height, subsamp);
        dstPlanes[i] = (unsigned char *)malloc(planeSizes[i]);
        if (!dstPlanes[i]) {
            for (int j = 0; j < i; j++) free(dstPlanes[j]);
            tjDestroy(handle);
            return 0;
        }
    }

    // Call the function-under-test
    int result = tj3EncodeYUVPlanes8(handle, srcBuf, width, pitch, height, subsamp, dstPlanes, planeSizes);
    if (result != 0) {
        for (int i = 0; i < 3; i++) free(dstPlanes[i]);
        tjDestroy(handle);
        return 0;
    }

    // Clean up
    for (int i = 0; i < 3; i++) {
        free(dstPlanes[i]);
    }
    tjDestroy(handle);

    return 0;
}