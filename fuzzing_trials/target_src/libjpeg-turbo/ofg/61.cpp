#include <cstdint>
#include <cstdlib>
#include <cstdio>

// Assuming the function is part of a C library, we wrap it with extern "C"
extern "C" {
    // Include the necessary header where tjGetErrorStr is declared
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Call the function-under-test
    char *errorStr = tjGetErrorStr();

    // Print the error string to ensure the function is being called
    if (errorStr != nullptr) {
        printf("Error: %s\n", errorStr);
    }

    return 0;
}