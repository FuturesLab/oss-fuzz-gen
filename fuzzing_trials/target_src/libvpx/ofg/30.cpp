#include <cstdint>
#include <cstdlib>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Use VP8 as the codec interface
    vpx_codec_dec_cfg_t dec_cfg;
    vpx_codec_flags_t flags = 0;
    int ver = VPX_DECODER_ABI_VERSION;

    // Initialize dec_cfg with some values
    dec_cfg.threads = 1;
    dec_cfg.w = 640;  // Example width
    dec_cfg.h = 480;  // Example height

    // Call the function-under-test
    vpx_codec_err_t result = vpx_codec_dec_init_ver(&codec_ctx, iface, &dec_cfg, flags, ver);

    // Clean up
    if (result == VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
    }

    return 0;
}