#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Initialize variables for tj3SaveImage16 function
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        return 0;
    }

    // Prepare a non-null file name string
    const char *filename = "test_output.ppm";

    // Prepare a non-null J16SAMPLE array
    uint16_t *sampleArray = (uint16_t *)malloc(size * sizeof(uint16_t));
    if (!sampleArray) {
        tj3Destroy(handle);
        return 0;
    }
    // Copy input data to sampleArray
    memcpy(sampleArray, data, size * sizeof(uint16_t));

    // Set image dimensions and other parameters
    int width = 10;  // Arbitrary non-zero width
    int height = 10; // Arbitrary non-zero height
    int pitch = width * sizeof(uint16_t);
    int flags = 0;   // No specific flags

    // Call the function-under-test
    tj3SaveImage16(handle, filename, sampleArray, width, pitch, height, flags);

    // Clean up
    free(sampleArray);
    tj3Destroy(handle);

    return 0;
}