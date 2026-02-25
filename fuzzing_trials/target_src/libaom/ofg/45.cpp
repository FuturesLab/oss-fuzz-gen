#include <cstdint>
#include <cstddef>
#include <iostream>

// Include the AOM codec header file
extern "C" {
#include <aom/aom_codec.h>
}

// Fuzzing harness for the aom_codec_version_str function
extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_str = aom_codec_version_str();

    // Print the version string to demonstrate the call (optional)
    if (version_str != nullptr) {
        std::cout << "AOM Codec Version: " << version_str << std::endl;
    }

    // Since the function does not take any input parameters, we do not need to use `data` or `size`.

    return 0;
}