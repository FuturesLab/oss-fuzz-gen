#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int width = ((int*)data)[0];
    int height = ((int*)data)[1];
    int jpegSubsamp = ((int*)data)[2];

    // Call the function-under-test
    size_t bufferSize = tj3JPEGBufSize(width, height, jpegSubsamp);

    // Optionally, print the result for debugging purposes
    printf("Buffer Size: %zu\n", bufferSize);

    return 0;
}