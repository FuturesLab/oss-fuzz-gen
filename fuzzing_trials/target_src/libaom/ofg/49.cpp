#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Declare and initialize the codec context
    aom_codec_ctx_t codec_ctx;

    // Ensure the codec context is not NULL
    if (size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Copy the data into the codec context
    memcpy(&codec_ctx, data, sizeof(aom_codec_ctx_t));

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_destroy(&codec_ctx);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}