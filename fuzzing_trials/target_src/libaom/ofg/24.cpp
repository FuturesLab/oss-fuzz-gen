#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    // Include the necessary headers for the AOM codec
    #include <aom/aom_codec.h>
}

// Fuzzing harness for the function aom_codec_version_extra_str
extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure that the input data is valid and not NULL
    if (data == nullptr || size == 0) {
        return 0; // No valid input to process
    }

    // Call the function under test
    const char *version_extra = aom_codec_version_extra_str();

    // Print the version extra string (for debugging purposes)
    if (version_extra != nullptr) {
        std::cout << "AOM Codec Version Extra: " << version_extra << std::endl;
    }

    return 0;
}