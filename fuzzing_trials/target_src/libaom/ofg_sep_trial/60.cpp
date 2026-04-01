#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio> // Include the necessary header for printf

extern "C" {
#include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for aom_codec_ctx_t structure
    if (size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Allocate memory for aom_codec_ctx_t and initialize it with input data
    aom_codec_ctx_t codec_ctx;
    std::memcpy(&codec_ctx, data, sizeof(aom_codec_ctx_t));

    // Call the function under test
    const char *error_msg = aom_codec_error(&codec_ctx);

    // Check the returned error message
    if (error_msg != nullptr) {
        // Print the error message for debugging purposes
        // In a real fuzzing scenario, you might want to log this information
        // or handle it differently
        printf("Error: %s\n", error_msg);
    }

    return 0;
}