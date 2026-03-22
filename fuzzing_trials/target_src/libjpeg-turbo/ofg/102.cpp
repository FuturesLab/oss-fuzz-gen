#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract four integers
    if (size < sizeof(int) * 4) {
        return 0;
    }

    // Extract four integers from the input data
    int width = *(reinterpret_cast<const int*>(data));
    int height = *(reinterpret_cast<const int*>(data + sizeof(int)));
    int subsamp = *(reinterpret_cast<const int*>(data + 2 * sizeof(int)));
    int align = *(reinterpret_cast<const int*>(data + 3 * sizeof(int)));

    // Call the function-under-test
    unsigned long bufferSize = tjBufSizeYUV2(width, height, subsamp, align);

    // Use the bufferSize to avoid compiler optimizations removing the call
    volatile unsigned long result = bufferSize;
    (void)result;

    return 0;
}