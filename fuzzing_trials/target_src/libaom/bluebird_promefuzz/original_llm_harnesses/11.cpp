// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
#include <iostream>
#include <cstring>
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aom_decoder.h"
#include "aomcx.h"
#include "aomdx.h"

static void InitializeCodecContext(aom_codec_ctx_t &ctx) {
    memset(&ctx, 0, sizeof(ctx));
    ctx.name = "AV1";
    ctx.iface = aom_codec_av1_cx();
    ctx.err = AOM_CODEC_OK;
    ctx.init_flags = 0;
    ctx.priv = nullptr;
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 6) return 0;

    aom_codec_ctx_t codec_ctx;
    InitializeCodecContext(codec_ctx);

    int auto_tiles = static_cast<int>(Data[0]);
    int skip_postproc_filtering = static_cast<int>(Data[1]);
    int enable_rate_guide_deltaq = static_cast<int>(Data[2]);
    int enable_adaptive_sharpness = static_cast<int>(Data[3]);
    int sharpness_level = static_cast<int>(Data[4]);
    int enable_restoration = static_cast<int>(Data[5]);

    aom_codec_control(&codec_ctx, AV1E_SET_AUTO_TILES, auto_tiles);
    aom_codec_control(&codec_ctx, AV1E_SET_SKIP_POSTPROC_FILTERING, skip_postproc_filtering);
    aom_codec_control(&codec_ctx, AV1E_ENABLE_RATE_GUIDE_DELTAQ, enable_rate_guide_deltaq);
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS, enable_adaptive_sharpness);
    aom_codec_control(&codec_ctx, AOME_SET_SHARPNESS, sharpness_level);
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_RESTORATION, enable_restoration);

    aom_codec_destroy(&codec_ctx);
    return 0;
}