#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to extract three integers
    if (size < 5) {
        return 0;
    }

    // Extract three integers from the input data
    int width = static_cast<int>(data[0] | (data[1] << 8));
    int height = static_cast<int>(data[2] | (data[3] << 8));
    int jpegSubsamp = static_cast<int>(data[4] % 5); // Valid subsample values are typically 0-4

    // Call the function-under-test
    size_t bufferSize = tj3JPEGBufSize(width, height, jpegSubsamp);

    // Print the result for debugging purposes
    printf("Buffer size: %zu\n", bufferSize);

    return 0;
}