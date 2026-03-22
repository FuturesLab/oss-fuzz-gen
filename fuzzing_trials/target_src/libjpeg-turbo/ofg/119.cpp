#include <stdint.h>
#include <stddef.h>
#include <stdio.h> // Include for printf

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h" // Correct path for turbojpeg.h
}

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Call the function-under-test
    char *errorStr = tjGetErrorStr();

    // Ensure that the function call is used in some way
    if (errorStr != nullptr) {
        // Print the error string for debugging purposes
        // In a real fuzzing harness, you might log this or perform other checks
        printf("Error String: %s\n", errorStr);
    }

    return 0;
}