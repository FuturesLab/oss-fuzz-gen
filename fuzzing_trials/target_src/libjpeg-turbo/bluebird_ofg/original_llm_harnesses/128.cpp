#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract four integers
    if (size < 16) return 0;

    // Extract four integers from the input data
    int width = *(reinterpret_cast<const int*>(data));
    int height = *(reinterpret_cast<const int*>(data + 4));
    int subsamp = *(reinterpret_cast<const int*>(data + 8));
    int align = *(reinterpret_cast<const int*>(data + 12));

    // Call the function-under-test
    unsigned long result = tjBufSizeYUV2(width, height, subsamp, align);

    // Use the result in some way to avoid optimization issues
    volatile unsigned long use_result = result;
    (void)use_result;

    return 0;
}