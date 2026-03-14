#include <cstdint>
#include <cstddef>

extern "C" {
    // Include the necessary header for the function under test
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Call the function under test
    const char *version_extra_str = aom_codec_version_extra_str();

    // Ensure the returned string is not NULL and perform some basic operations
    if (version_extra_str != nullptr) {
        // For fuzzing purposes, we can check the length of the string
        size_t length = 0;
        while (version_extra_str[length] != '\0') {
            length++;
        }
    }

    return 0;
}