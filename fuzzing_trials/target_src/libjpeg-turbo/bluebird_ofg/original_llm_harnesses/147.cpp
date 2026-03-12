#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Ensure the size is at least 1 to allocate non-NULL memory
    if (size < 1) {
        return 0;
    }

    // Allocate memory using the provided data
    unsigned char *buffer = static_cast<unsigned char*>(malloc(size));
    if (buffer == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the allocated buffer
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = data[i];
    }

    // Call the function-under-test
    tjFree(buffer);

    return 0;
}