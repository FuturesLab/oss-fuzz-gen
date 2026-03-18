#include <stdint.h>
#include <stddef.h>

// Assuming the function is part of a C library, we wrap it in extern "C"
extern "C" {
    // Include the necessary header for the function-under-test
    #include <aom/aom_codec.h>
}

// Fuzzing harness for the function aom_codec_version_str
extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_str = aom_codec_version_str();

    // Since the function returns a string, we can perform basic checks
    if (version_str != NULL) {
        // Optionally, we could print or log the version string
        // For fuzzing purposes, we just ensure it's not NULL
    }

    return 0;
}