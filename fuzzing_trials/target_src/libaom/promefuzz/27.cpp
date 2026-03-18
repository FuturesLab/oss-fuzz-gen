// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aomcx.h>
}

#include <cstdint>
#include <cstdio>

static void initialize_codec_context(aom_codec_ctx_t &codec_ctx, aom_codec_iface_t *iface) {
    aom_codec_enc_cfg_t cfg;
    aom_codec_err_t res = aom_codec_enc_config_default(iface, &cfg, 0);
    if (res != AOM_CODEC_OK) return;
    res = aom_codec_enc_init(&codec_ctx, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) return;
}

static void cleanup_codec_context(aom_codec_ctx_t &codec_ctx) {
    aom_codec_destroy(&codec_ctx);
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_ctx_t codec_ctx;
    initialize_codec_context(codec_ctx, iface);

    uint32_t enable_low_complexity_decode = Data[0] % 2;
    uint32_t fp_mt = Data[1] % 2;
    uint32_t skip_postproc_filtering = Data[2] % 2;
    uint32_t tile_rows = Data[3] % 64; // Arbitrary limit for tile rows
    uint32_t disable_trellis_quant = Data[4] % 2;
    uint32_t enable_obmc = Data[5] % 2;

    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_LOW_COMPLEXITY_DECODE, enable_low_complexity_decode);
    aom_codec_control(&codec_ctx, AV1E_SET_FP_MT, fp_mt);
    aom_codec_control(&codec_ctx, AV1E_SET_SKIP_POSTPROC_FILTERING, skip_postproc_filtering);
    aom_codec_control(&codec_ctx, AV1E_SET_TILE_ROWS, tile_rows);
    aom_codec_control(&codec_ctx, AV1E_SET_DISABLE_TRELLIS_QUANT, disable_trellis_quant);
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_OBMC, enable_obmc);

    cleanup_codec_context(codec_ctx);

    return 0;
}