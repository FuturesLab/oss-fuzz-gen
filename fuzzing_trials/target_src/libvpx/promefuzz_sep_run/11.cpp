// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_enc_config_default at vpx_encoder.c:157:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:29:17 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_vp8_cx at vp8_cx_iface.c:1428:1 in vp8cx.h
// vpx_codec_vp9_cx at vp9_cx_iface.c:2290:1 in vp8cx.h
// vpx_codec_encode at vpx_encoder.c:193:17 in vpx_encoder.h
// vpx_codec_encode at vpx_encoder.c:193:17 in vpx_encoder.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "vpx_encoder.h"
#include "vp8dx.h"
#include "vp8cx.h"

static vpx_codec_err_t initialize_encoder(vpx_codec_ctx_t *ctx, vpx_codec_enc_cfg_t *cfg, vpx_codec_iface_t *iface) {
    vpx_codec_err_t res = vpx_codec_enc_config_default(iface, cfg, 0);
    if (res != VPX_CODEC_OK) {
        std::cerr << "Failed to get default codec config." << std::endl;
        return res;
    }

    res = vpx_codec_enc_init_ver(ctx, iface, cfg, 0, VPX_ENCODER_ABI_VERSION);
    if (res != VPX_CODEC_OK) {
        std::cerr << "Failed to initialize codec." << std::endl;
    }
    return res;
}

static void cleanup_encoder(vpx_codec_ctx_t *ctx) {
    vpx_codec_destroy(ctx);
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_image_t)) {
        return 0;
    }

    // Initialize encoder for VP8
    vpx_codec_ctx_t codec_ctx_vp8;
    vpx_codec_enc_cfg_t cfg_vp8;
    vpx_codec_iface_t *iface_vp8 = vpx_codec_vp8_cx();
    if (initialize_encoder(&codec_ctx_vp8, &cfg_vp8, iface_vp8) != VPX_CODEC_OK) {
        return 0;
    }

    // Initialize encoder for VP9
    vpx_codec_ctx_t codec_ctx_vp9;
    vpx_codec_enc_cfg_t cfg_vp9;
    vpx_codec_iface_t *iface_vp9 = vpx_codec_vp9_cx();
    if (initialize_encoder(&codec_ctx_vp9, &cfg_vp9, iface_vp9) != VPX_CODEC_OK) {
        return 0;
    }

    // Create a dummy image from the input data
    vpx_image_t img;
    std::memcpy(&img, Data, sizeof(vpx_image_t));
    img.img_data = const_cast<uint8_t *>(Data);
    img.planes[0] = const_cast<uint8_t *>(Data);

    // Encode using VP8
    vpx_codec_encode(&codec_ctx_vp8, &img, 0, 1, 0, VPX_DL_REALTIME);

    // Encode using VP9
    vpx_codec_encode(&codec_ctx_vp9, &img, 0, 1, 0, VPX_DL_REALTIME);

    // Cleanup
    cleanup_encoder(&codec_ctx_vp8);
    cleanup_encoder(&codec_ctx_vp9);

    return 0;
}