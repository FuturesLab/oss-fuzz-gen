#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

// Include the necessary header for the function-under-test
extern "C" {
#include <aom/aom_codec.h>
}

// Fuzzing harness for aom_codec_error
extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Declare and initialize the aom_codec_ctx_t structure
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx)); // Initialize with zeroes

    // Ensure the data is large enough to fill the codec_ctx structure
    if (size >= sizeof(codec_ctx)) {
        // Copy data into codec_ctx, ensuring it is not NULL
        memcpy(&codec_ctx, data, sizeof(codec_ctx));

        // Call the function-under-test
        const char *error_message = aom_codec_error(&codec_ctx);

        // Optionally print the error message for debugging
        if (error_message != NULL) {
            std::cout << "Error Message: " << error_message << std::endl;
        }
    }

    return 0;
}