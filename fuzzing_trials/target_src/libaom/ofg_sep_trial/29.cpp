#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h> // Include this header for aom_codec_av1_dx
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec_ctx;
    aom_codec_err_t err;

    // Initialize the codec context with a decoder interface
    err = aom_codec_dec_init(&codec_ctx, aom_codec_av1_dx(), NULL, 0);
    if (err != AOM_CODEC_OK) {
        return 0; // Initialization failed, exit early
    }

    // Call the function-under-test
    err = aom_codec_decode(&codec_ctx, data, size, NULL);

    // Destroy the codec context to clean up resources
    aom_codec_destroy(&codec_ctx);

    return 0;
}