#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    // Include the AOM codec header where the function is declared
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Since the function aom_codec_version_str() does not take parameters,
    // we can directly call it without needing to manipulate input data.

    // Call the function under test
    const char *version_str = aom_codec_version_str();

    // Print the version string to observe the output (for debugging purposes)
    // Note: In a real fuzzing context, you might not print but rather log or analyze the output.
    if (version_str != nullptr) {
        std::cout << "AOM Codec Version: " << version_str << std::endl;
    }

    // Return 0 as per the LLVMFuzzerTestOneInput convention
    return 0;
}