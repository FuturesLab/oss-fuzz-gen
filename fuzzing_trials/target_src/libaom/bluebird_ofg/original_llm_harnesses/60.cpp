#include <cstdint>
#include <cstddef>
#include <iostream>

extern "C" {
    // Include the header file where `aom_codec_version_str` is declared
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_str = aom_codec_version_str();

    // Output the version string to verify the function call
    // This is optional and for debugging purposes only
    std::cout << "AOM Codec Version: " << version_str << std::endl;

    return 0;
}