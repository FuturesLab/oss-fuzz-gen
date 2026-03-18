#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Call the function-under-test
    char *errorStr = tjGetErrorStr();

    // Use the returned error string in some way to ensure it is accessed
    // For this fuzzer, we'll just check if it's not NULL and print it
    if (errorStr != NULL) {
        // Normally, you might log or further process the error string
        // For this fuzz test, we'll just ensure it was accessed
        volatile char *access = errorStr;
        (void)access; // Prevent unused variable warning
    }

    return 0;
}