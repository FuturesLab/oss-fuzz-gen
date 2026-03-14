#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Allocate memory for the buffer to be freed
    unsigned char *buffer = (unsigned char *)malloc(size);
    if (buffer == NULL) {
        return 0; // Allocation failed, exit the fuzzer
    }

    // Copy the input data to the buffer
    for (size_t i = 0; i < size; i++) {
        buffer[i] = data[i];
    }

    // Call the function-under-test
    tjFree(buffer);

    return 0;
}