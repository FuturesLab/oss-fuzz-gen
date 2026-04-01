#include <cstdint>
#include <cstddef>
#include <iostream>

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version = aom_codec_version();

    // Output the codec version for debugging purposes
    std::cout << "AOM Codec Version: " << version << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}