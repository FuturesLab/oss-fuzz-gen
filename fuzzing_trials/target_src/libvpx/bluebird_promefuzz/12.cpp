#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "/src/libvpx/vpx/vpx_codec.h"
#include "/src/libvpx/vpx/vp8cx.h"
#include "vpx/vpx_decoder.h"
#include "/src/libvpx/vpx/vpx_encoder.h"
#include "vpx/vp8dx.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

static void dummy_put_frame_cb(void *user_priv, const vpx_image_t *img) {
  // Dummy callback function for put_frame
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize decoder context
    vpx_codec_ctx_t dec_ctx;
    vpx_codec_iface_t *dec_iface = vpx_codec_vp8_dx();
    vpx_codec_dec_cfg_t dec_cfg = {0};
    vpx_codec_err_t dec_res = vpx_codec_dec_init_ver(&dec_ctx, dec_iface, &dec_cfg, 0, VPX_DECODER_ABI_VERSION);
    if (dec_res != VPX_CODEC_OK) return 0;

    // Register dummy callback
    vpx_codec_register_put_frame_cb(&dec_ctx, dummy_put_frame_cb, nullptr);

    // Decode the input data
    vpx_codec_decode(&dec_ctx, Data, static_cast<unsigned int>(Size), nullptr, 0);

    // Signal end of data
    vpx_codec_decode(&dec_ctx, nullptr, 0, nullptr, 0);

    // Cleanup decoder context
    vpx_codec_destroy(&dec_ctx);

    // Initialize encoder context
    vpx_codec_ctx_t enc_ctx;
    vpx_codec_iface_t *enc_iface = vpx_codec_vp8_cx();
    vpx_codec_enc_cfg_t enc_cfg;
    if (vpx_codec_enc_config_default(enc_iface, &enc_cfg, 0) != VPX_CODEC_OK) return 0;
    enc_cfg.g_threads = 1;
    enc_cfg.g_w = 320;
    enc_cfg.g_h = 240;
    enc_cfg.g_timebase.num = 1;
    enc_cfg.g_timebase.den = 30;

    vpx_codec_err_t enc_res = vpx_codec_enc_init(&enc_ctx, enc_iface, &enc_cfg, 0);
    if (enc_res != VPX_CODEC_OK) return 0;

    // Set output buffer
    vpx_fixed_buf_t cx_data_buf;
    cx_data_buf.buf = malloc(1000);
    cx_data_buf.sz = 1000;
    vpx_codec_set_cx_data_buf(&enc_ctx, &cx_data_buf, 0, 0);

    // Initialize multi-encoder instance
    vpx_codec_ctx_t multi_enc_ctx[1];
    vpx_codec_enc_cfg_t multi_enc_cfg[1];
    multi_enc_cfg[0] = enc_cfg;
    vpx_rational_t dsf = {1, 1};
    vpx_codec_enc_init_multi_ver(multi_enc_ctx, enc_iface, multi_enc_cfg, 1, 0, &dsf, VPX_ENCODER_ABI_VERSION);

    // Cleanup multi-encoder context
    for (int i = 0; i < 1; ++i) {
        vpx_codec_destroy(&multi_enc_ctx[i]);
    }

    // Cleanup encoder context
    vpx_codec_destroy(&enc_ctx);
    free(cx_data_buf.buf);

    return 0;
}