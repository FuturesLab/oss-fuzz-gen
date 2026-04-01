#include <cstdint>
#include <cstddef>
#include <cstdio>

// Assuming the function is part of a C library, we wrap it in extern "C"
extern "C" {
    const char * aom_codec_version_str();
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_str = aom_codec_version_str();

    // Print the version string to ensure the function is called
    if (version_str != nullptr) {
        printf("AOM Codec Version: %s\n", version_str);
    }

    return 0;
}