#include <cstdint>
#include <cstddef>
#include <cstring> // Include this for std::memcpy

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid aom_codec_ctx_t object
    if (size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Create an aom_codec_ctx_t object from the input data
    aom_codec_ctx_t codec_ctx;
    // Copy data into the codec_ctx structure
    std::memcpy(&codec_ctx, data, sizeof(aom_codec_ctx_t));

    // Call the function-under-test
    const char *error_detail = aom_codec_error_detail(&codec_ctx);

    // Use the result to avoid compiler optimizations that might remove the call
    if (error_detail != nullptr) {
        // Do something with error_detail, like logging or further processing
    }

    return 0;
}