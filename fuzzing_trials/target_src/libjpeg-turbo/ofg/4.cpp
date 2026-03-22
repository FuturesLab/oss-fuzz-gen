#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"

    // Including the function signature from the library
    size_t tj3JPEGBufSize(int width, int height, int jpegSubsamp);
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int width = *((int*)data);
    int height = *((int*)(data + sizeof(int)));
    int jpegSubsamp = *((int*)(data + 2 * sizeof(int)));

    // Call the function-under-test with the extracted integers
    size_t result = tj3JPEGBufSize(width, height, jpegSubsamp);

    // Use the result in some way (e.g., print it, or just return 0)
    // For fuzzing, we typically don't need to do anything with the result
    (void)result; // Suppress unused variable warning

    return 0;
}