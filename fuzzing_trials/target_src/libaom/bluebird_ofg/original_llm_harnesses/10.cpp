#include <stdint.h>
#include <stddef.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Declare and initialize all necessary variables
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx(); // Use AV1 decoder interface
    aom_codec_dec_cfg_t cfg;
    aom_codec_flags_t flags = 0; // Initialize flags to zero
    int ver = AOM_DECODER_ABI_VERSION; // Use the current decoder ABI version

    // Initialize codec configuration with some default values
    cfg.threads = 1; // Single-threaded decoding
    cfg.w = 640; // Default width
    cfg.h = 480; // Default height
    cfg.allow_lowbitdepth = 1; // Allow low bit depth

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_dec_init_ver(&codec_ctx, iface, &cfg, flags, ver);

    // Clean up by destroying the codec context if it was initialized successfully
    if (result == AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
    }

    return 0;
}