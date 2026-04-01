#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, return early
    }

    // Prepare the output parameters
    int width = 0, height = 0, jpegSubsamp = 0, jpegColorspace = 0;

    // Call the function-under-test
    int result = tjDecompressHeader3(handle, data, (unsigned long)size, &width, &height, &jpegSubsamp, &jpegColorspace);

    // Clean up the TurboJPEG decompressor
    tjDestroy(handle);

    return 0; // Always return 0 from the fuzzer function
}