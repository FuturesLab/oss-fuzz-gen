#include <cstdint>
#include <cstddef>

extern "C" {
    // Include the header where aom_codec_version_extra_str is declared
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_extra_str = aom_codec_version_extra_str();

    // Optional: Use the returned string in some way to prevent compiler optimizations from removing the call
    if (version_extra_str != nullptr) {
        // For example, check the length of the string
        size_t length = 0;
        while (version_extra_str[length] != '\0') {
            length++;
        }
    }

    return 0;
}