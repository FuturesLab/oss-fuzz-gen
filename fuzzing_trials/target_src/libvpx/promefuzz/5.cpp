// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_img_alloc at vpx_image.c:162:14 in vpx_image.h
// vpx_codec_vp8_cx at vp8_cx_iface.c:1428:1 in vp8cx.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_enc_config_default at vpx_encoder.c:157:17 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_enc_init_ver at vpx_encoder.c:29:17 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_control_ at vpx_codec.c:89:17 in vpx_codec.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
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
#include <iostream>
#include "vpx_codec.h"
#include "vpx_image.h"
#include "vp8cx.h"
#include "vpx_encoder.h"
#include "vp8dx.h"

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_img_fmt_t) + 3 * sizeof(unsigned int)) {
        return 0; // Not enough data to proceed
    }

    const vpx_img_fmt_t fmt = static_cast<vpx_img_fmt_t>(Data[0]);
    const unsigned int d_w = static_cast<unsigned int>(Data[1]) % 0x08000000;
    const unsigned int d_h = static_cast<unsigned int>(Data[2]) % 0x08000000;
    const unsigned int align = static_cast<unsigned int>(Data[3]) % 65536;

    vpx_image_t *img = vpx_img_alloc(nullptr, fmt, d_w, d_h, align);
    if (!img) {
        return 0; // Allocation failed
    }

    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    const char *iface_name = vpx_codec_iface_name(iface);
    if (!iface_name) {
        vpx_img_free(img);
        return 0;
    }

    vpx_codec_enc_cfg_t cfg;
    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        vpx_img_free(img);
        return 0;
    }

    vpx_codec_ctx_t codec;
    if (vpx_codec_enc_init_ver(&codec, iface, &cfg, 0, VPX_ENCODER_ABI_VERSION) != VPX_CODEC_OK) {
        vpx_img_free(img);
        return 0;
    }

    vpx_codec_err_t ctrl_err = vpx_codec_control_(&codec, VP8E_SET_CPUUSED, 2);
    if (ctrl_err != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        vpx_img_free(img);
        return 0;
    }

    vpx_img_free(img);

    if (vpx_codec_destroy(&codec) != VPX_CODEC_OK) {
        return 0;
    }

    return 0;
}