#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Ensure there's enough data to work with
    }

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // Initialization failed
    }

    // Prepare input parameters for tj3SaveImage16
    const char *filename = "test_output.ppm"; // Dummy filename
    const uint16_t *imageBuffer = reinterpret_cast<const uint16_t *>(data); // Correct type for J16SAMPLE
    int width = 2; // Minimal width for testing
    int height = 2; // Minimal height for testing
    int pitch = width * sizeof(uint16_t); // Row size
    int pixelFormat = TJPF_RGB; // Use RGB format

    // Call the function-under-test
    tj3SaveImage16(handle, filename, imageBuffer, width, pitch, height, pixelFormat);

    // Clean up
    tj3Destroy(handle);

    return 0;
}