extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio> // For printing debug information

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        return 0;
    }

    // Define YUV image dimensions
    int width = 640;  // Example width
    int height = 480; // Example height
    int subsamp = TJSAMP_420; // Example subsampling

    // Calculate the size of the YUV buffer
    size_t yuvSize = tj3YUVBufSize(width, 4, height, subsamp);
    if (size < yuvSize) {
        tj3Destroy(handle);
        return 0;
    }

    // Allocate memory for the YUV image
    unsigned char *yuvBuf = (unsigned char *)malloc(yuvSize);
    if (!yuvBuf) {
        tj3Destroy(handle);
        return 0;
    }

    // Copy the input data to the YUV buffer
    memcpy(yuvBuf, data, yuvSize);

    // Allocate memory for the compressed image
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    int result = tj3CompressFromYUV8(handle, yuvBuf, width, 4, height, &jpegBuf, &jpegSize);

    // Ensure the function under test is invoked properly
    if (result == 0 && jpegBuf != nullptr && jpegSize > 0) {
        // Do something with jpegBuf to ensure it's used, e.g., validate or process it
        printf("Compressed JPEG size: %zu\n", jpegSize); // Print the size of the compressed image
    } else {
        printf("Compression failed or produced no output.\n");
    }

    // Clean up
    free(yuvBuf);
    if (jpegBuf) {
        tj3Free(jpegBuf);
    }
    tj3Destroy(handle);

    return 0;
}