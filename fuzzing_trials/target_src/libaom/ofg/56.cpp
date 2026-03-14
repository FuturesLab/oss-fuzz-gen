extern "C" {
    #include <aom/aom_codec.h>
}

#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_str = aom_codec_version_str();

    // Ensure the result is not NULL and perform a basic operation
    if (version_str != nullptr) {
        // Print the version string (for debugging purposes)
        // Note: In actual fuzzing, printing is typically avoided for performance reasons
        // printf("AOM Codec Version: %s\n", version_str);
    }

    return 0;
}