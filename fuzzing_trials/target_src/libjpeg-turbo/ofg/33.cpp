#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // Initialization failed
    }

    // Extract parameters from the input data
    int width = (data[0] << 8) + data[1];
    int height = (data[2] << 8) + data[3];
    int subsamp = data[4] % 4; // Limit subsampling to valid values [0, 3]
    int flags = data[5] % 2;   // Limit flags to valid values [0, 1]

    // Ensure width and height are positive
    width = width > 0 ? width : 1;
    height = height > 0 ? height : 1;

    // Calculate the YUV buffer size
    int yuvSize = tjBufSizeYUV2(width, 4, height, subsamp);
    if (yuvSize <= 0 || yuvSize > static_cast<int>(size - 6)) {
        tjDestroy(handle);
        return 0; // Invalid YUV buffer size
    }

    // Create a YUV buffer and copy data into it
    const unsigned char *yuvBuffer = data + 6;

    // Allocate output buffer
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    // Call the function under test
    int result = tjCompressFromYUV(handle, yuvBuffer, width, 4, height, subsamp, &jpegBuf, &jpegSize, 80, flags);

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return result;
}