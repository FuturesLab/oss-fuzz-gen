#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to extract three integers
    if (size < sizeof(int) * 3) {
        return 0;
    }

    // Extract three integers from the input data
    int width = *(reinterpret_cast<const int*>(data));
    int height = *(reinterpret_cast<const int*>(data + sizeof(int)));
    int subsamp = *(reinterpret_cast<const int*>(data + 2 * sizeof(int)));

    // Call the function-under-test
    unsigned long bufferSize = TJBUFSIZEYUV(width, height, subsamp);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile unsigned long result = bufferSize;
    (void)result;

    return 0;
}