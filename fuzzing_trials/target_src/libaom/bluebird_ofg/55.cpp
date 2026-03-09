#include <cstdint>
#include <cstddef>
#include <iostream>

extern "C" {
    // Include the necessary header for the function-under-test
    #include "/src/aom/aom/aom_codec.h"
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_extra_str = aom_codec_version_extra_str();

    // Output the result for debugging purposes
    if (version_extra_str != nullptr) {
        std::cout << "Version Extra String: " << version_extra_str << std::endl;
    } else {
        std::cout << "Version Extra String is NULL" << std::endl;
    }

    return 0;
}