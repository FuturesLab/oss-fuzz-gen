#include <cstdint>
#include <cstdlib>
#include <iostream>

// Include the necessary header for the function-under-test
extern "C" {
    // Include the correct path for the turbojpeg header
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    // Alternatively, you can use one of the other paths if needed:
    // #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    // #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

// Fuzzing harness for the function TJBUFSIZEYUV
extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Initialize variables with non-zero values to ensure they are not NULL
    int width = 1;
    int height = 1;
    int subsamp = TJSAMP_420; // Use a valid subsampling option

    // Call the function-under-test
    unsigned long bufferSize = TJBUFSIZEYUV(width, height, subsamp);

    // Print the result to verify the function call (optional)
    std::cout << "Buffer size: " << bufferSize << std::endl;

    return 0;
}