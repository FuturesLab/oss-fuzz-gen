#include <cstdint>
#include <cstdlib>
#include <aom/aom_codec.h>
#include <aom/aomcx.h> // Include the encoder header for aom_codec_av1_cx and aom_codec_enc_init

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aomcx.h>
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Initialize the codec context
    aom_codec_ctx_t codec_ctx;

    // Ensure that the codec context is non-NULL by allocating memory
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (iface == NULL) {
        return 0;
    }

    // Initialize the codec context with the interface
    if (aom_codec_enc_init(&codec_ctx, iface, NULL, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test
    const char *error_detail = aom_codec_error_detail(&codec_ctx);

    // Check the result (optional, for debugging purposes)
    if (error_detail != NULL) {
        // Print the error detail (in a real fuzzing environment, you might log this)
        // printf("Error Detail: %s\n", error_detail);
    }

    // Destroy the codec context to clean up
    aom_codec_destroy(&codec_ctx);

    return 0;
}