#include <cstdint>
#include <cstdlib>
#include <iostream>

extern "C" {
    // Include the necessary header for the function under test
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Initialize a variable to hold the codec version
    int codec_version;

    // Call the function under test
    codec_version = aom_codec_version();

    // Optionally, you can print the codec version for debugging purposes
    // However, in a fuzzing context, it's generally better to avoid I/O
    // std::cout << "Codec Version: " << codec_version << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}