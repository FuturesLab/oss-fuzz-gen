#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Ensure we have enough data to read the width, height, and subsampling
    if (size < sizeof(int) * 3) {
        tjDestroy(handle);
        return 0;
    }

    // Extract width, height, and subsampling from the data
    int width = 0, height = 0, subsamp = 0;
    std::memcpy(&width, data, sizeof(int));
    std::memcpy(&height, data + sizeof(int), sizeof(int));
    std::memcpy(&subsamp, data + 2 * sizeof(int), sizeof(int));

    // Ensure width and height are positive and reasonable
    width = abs(width) % 4096 + 1;
    height = abs(height) % 4096 + 1;

    // Allocate buffer for YUV image
    int yuvSize = tjBufSizeYUV2(width, 4, height, subsamp); // Fixed by adding the 'align' parameter
    unsigned char *yuvBuffer = static_cast<unsigned char *>(malloc(yuvSize));
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompressToYUV2(handle, data, size, yuvBuffer, width, 4, height, subsamp);

    // Clean up
    free(yuvBuffer);
    tjDestroy(handle);
    return 0;
}