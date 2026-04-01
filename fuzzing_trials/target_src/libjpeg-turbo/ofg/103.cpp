#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to proceed
    }

    // Extract width, height, and subsampling from the data
    int width = data[0] + 1;  // Ensure width is positive
    int height = data[1] + 1; // Ensure height is positive
    int subsamp = data[2] % 4; // Use a valid subsampling option (0-3)
    int align = (data[3] % 8) + 1; // Ensure alignment is between 1 and 8

    // Call the function-under-test
    unsigned long bufferSize = tjBufSizeYUV2(width, height, subsamp, align);

    // Allocate a buffer of the calculated size
    unsigned char *buffer = (unsigned char *)malloc(bufferSize);
    if (buffer == nullptr) {
        return 0; // Memory allocation failed
    }

    // Use the buffer in some way, here we just simulate processing
    memset(buffer, 0, bufferSize);

    // Free the allocated buffer
    free(buffer);

    // Return 0 to indicate success
    return 0;
}