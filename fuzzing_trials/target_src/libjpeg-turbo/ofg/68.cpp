#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Not enough data to proceed
    }

    // Initialize parameters for tj3CompressFromYUV8
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // Initialization failed
    }

    const unsigned char *srcBuf = data;
    int width = static_cast<int>(data[0]); // Set width from data
    int height = static_cast<int>(data[1]); // Set height from data
    int subsamp = static_cast<int>(data[2] % 3); // Ensure subsamp is a valid value

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    tj3CompressFromYUV8(handle, srcBuf, width, height, subsamp, &jpegBuf, &jpegSize);

    // Clean up
    if (jpegBuf != nullptr) {
        tj3Free(jpegBuf);
    }
    tj3Destroy(handle);

    return 0;
}