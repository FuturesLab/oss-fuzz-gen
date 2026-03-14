#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // Initialization failed
    }

    const unsigned char *srcBuf = data;
    int width = static_cast<int>(data[0]);  // Use first byte as width
    int height = static_cast<int>(data[1]); // Use second byte as height
    int subsamp = static_cast<int>(data[2] % 4); // Use third byte for subsampling, ensure valid range

    unsigned char *dstBuf = nullptr;
    size_t dstSize = 0;

    // Call the function-under-test
    int result = tj3CompressFromYUV8(handle, srcBuf, width, height, subsamp, &dstBuf, &dstSize);

    // Clean up
    if (dstBuf != nullptr) {
        tj3Free(dstBuf);
    }
    tj3Destroy(handle);

    return 0;
}