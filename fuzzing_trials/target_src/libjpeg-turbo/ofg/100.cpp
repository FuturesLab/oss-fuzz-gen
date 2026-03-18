#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Allocate memory to simulate a pointer that will be freed
    void *ptr = malloc(size > 0 ? size : 1); // Ensure at least 1 byte is allocated to avoid NULL

    // Call the function-under-test
    tj3Free(ptr);

    return 0;
}