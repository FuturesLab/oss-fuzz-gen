// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_cx at vp8_cx_iface.c:1428:1 in vp8cx.h
// vpx_codec_vp9_cx at vp9_cx_iface.c:2290:1 in vp8cx.h
// vpx_codec_enc_config_default at vpx_encoder.c:157:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:29:17 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_enc_config_default at vpx_encoder.c:157:17 in vpx_encoder.h
// vpx_codec_enc_init_ver at vpx_encoder.c:29:17 in vpx_encoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_version_str at vpx_codec.c:26:13 in vpx_codec.h
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
#include <cstring>
#include <cstdio>
#include "vpx_encoder.h"
#include "vp8dx.h"
#include "vpx_codec.h"
#include "vp8cx.h"

static void init_vpx_codec_ctx(vpx_codec_ctx_t *ctx) {
    memset(ctx, 0, sizeof(vpx_codec_ctx_t));
}

static void init_vpx_codec_enc_cfg(vpx_codec_enc_cfg_t *cfg) {
    memset(cfg, 0, sizeof(vpx_codec_enc_cfg_t));
    cfg->g_usage = 0;
    cfg->g_bit_depth = VPX_BITS_8;
    cfg->g_timebase.num = 1;
    cfg->g_timebase.den = 1000;
    cfg->g_error_resilient = 0;
    cfg->g_pass = VPX_RC_ONE_PASS;
    cfg->rc_end_usage = VPX_VBR;
    cfg->kf_mode = VPX_KF_AUTO;
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_codec_enc_cfg_t)) {
        return 0;
    }

    vpx_codec_ctx_t codec_ctx;
    init_vpx_codec_ctx(&codec_ctx);

    vpx_codec_enc_cfg_t enc_cfg;
    init_vpx_codec_enc_cfg(&enc_cfg);

    vpx_codec_iface_t *vp8_iface = vpx_codec_vp8_cx();
    vpx_codec_iface_t *vp9_iface = vpx_codec_vp9_cx();

    vpx_codec_err_t res = vpx_codec_enc_config_default(vp8_iface, &enc_cfg, 0);
    if (res == VPX_CODEC_OK) {
        res = vpx_codec_enc_init_ver(&codec_ctx, vp8_iface, &enc_cfg, 0, VPX_ENCODER_ABI_VERSION);
        if (res == VPX_CODEC_OK) {
            vpx_codec_destroy(&codec_ctx);
        }
    }

    res = vpx_codec_enc_config_default(vp9_iface, &enc_cfg, 0);
    if (res == VPX_CODEC_OK) {
        res = vpx_codec_enc_init_ver(&codec_ctx, vp9_iface, &enc_cfg, 0, VPX_ENCODER_ABI_VERSION);
        if (res == VPX_CODEC_OK) {
            vpx_codec_destroy(&codec_ctx);
        }
    }

    const char *iface_name = vpx_codec_iface_name(vp8_iface);
    if (iface_name) {
        printf("VP8 Interface Name: %s\n", iface_name);
    }

    iface_name = vpx_codec_iface_name(vp9_iface);
    if (iface_name) {
        printf("VP9 Interface Name: %s\n", iface_name);
    }

    const char *version_str = vpx_codec_version_str();
    if (version_str) {
        printf("Libvpx Version: %s\n", version_str);
    }

    return 0;
}