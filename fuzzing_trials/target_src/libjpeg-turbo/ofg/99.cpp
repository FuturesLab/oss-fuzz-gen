#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    
    void tj3Free(void *);
}

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Allocate memory for a buffer with the same size as the input data
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        return 0; // If allocation fails, return early
    }

    // Copy the input data into the buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    tj3Free(buffer);

    // Return 0 to indicate successful execution
    return 0;
}