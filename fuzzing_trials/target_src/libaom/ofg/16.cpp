#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>

extern "C" {
    aom_codec_err_t aom_codec_dec_init_ver(aom_codec_ctx_t *, aom_codec_iface_t *, const aom_codec_dec_cfg_t *, aom_codec_flags_t, int);
    aom_codec_iface_t* aom_codec_av1_dx();
    #define AOM_CODEC_USE_CURRENT_VERSION 1 // Define the current version if not defined
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *codec_iface = aom_codec_av1_dx(); // Using AV1 decoder interface
    aom_codec_dec_cfg_t dec_cfg;
    aom_codec_flags_t flags = 0; // No special flags
    int version = AOM_CODEC_USE_CURRENT_VERSION; // Use current version

    // Initialize the decoder configuration with sensible defaults
    dec_cfg.threads = 1; // Use a single thread
    dec_cfg.allow_lowbitdepth = 1; // Allow low bit depth
    dec_cfg.w = 640; // Width of the frame
    dec_cfg.h = 480; // Height of the frame

    // Ensure the input size is manageable
    if (size > 65536) {
        size = 65536; // Cap the size to avoid excessive memory usage
    }

    // Create a buffer for the input data
    uint8_t *input_data = (uint8_t *)malloc(size);
    if (input_data == NULL) {
        return 0; // Memory allocation failed
    }
    
    // Copy the input data to the buffer
    memcpy(input_data, data, size);

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_dec_init_ver(&codec_ctx, codec_iface, &dec_cfg, flags, version);

    // Clean up
    free(input_data);
    
    return result == AOM_CODEC_OK ? 0 : 1; // Return 0 on success, 1 on error
}