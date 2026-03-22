#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    int width = 0;
    int height = 0;
    int jpegSubsamp = 0;
    int jpegColorspace = 0;

    // Ensure size is non-zero and data is not NULL
    if (size > 0 && data != nullptr) {
        // Call the function-under-test
        tjDecompressHeader3(handle, data, (unsigned long)size, &width, &height, &jpegSubsamp, &jpegColorspace);
    }

    tjDestroy(handle);
    return 0;
}