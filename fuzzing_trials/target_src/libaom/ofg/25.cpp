#include <cstdint>
#include <cstddef>
#include <cstdio>

// Assuming the function aom_codec_version_extra_str is defined in aom codec library
extern "C" {
    const char * aom_codec_version_extra_str();
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Initialize a variable to hold the return value of the function
    const char *version_extra_str;

    // Call the function under test
    version_extra_str = aom_codec_version_extra_str();

    // Ensure that the function does not return NULL
    if (version_extra_str != nullptr) {
        // Print the version string for debugging purposes
        printf("AOM Codec Version Extra String: %s\n", version_extra_str);
    }

    return 0;
}