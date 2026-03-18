// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
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
#include <cstdlib>

static void initialize_codec(aom_codec_ctx_t *codec_ctx, aom_codec_iface_t *iface) {
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to get default codec config.\n");
        exit(1);
    }

    if (aom_codec_enc_init(codec_ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to initialize codec.\n");
        exit(1);
    }
}

static void cleanup_codec(aom_codec_ctx_t *codec_ctx) {
    if (aom_codec_destroy(codec_ctx) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to destroy codec.\n");
    }
}

static void fuzz_codec_controls(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    int cq_level = Data[0] % 64; // CQ level range
    if (aom_codec_control(codec_ctx, AOME_SET_CQ_LEVEL, cq_level) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set CQ level.\n");
    }

    if (Size < 2) return;
    int enable_auto_alt_ref = Data[1] % 2;
    if (aom_codec_control(codec_ctx, AOME_SET_ENABLEAUTOALTREF, enable_auto_alt_ref) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set auto alt ref.\n");
    }

    if (Size < 3) return;
    int num_spatial_layers = Data[2] % 5 + 1; // 1 to 5 layers
    if (aom_codec_control(codec_ctx, AOME_SET_NUMBER_SPATIAL_LAYERS, num_spatial_layers) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set number of spatial layers.\n");
    }

    int loop_filter_level;
    if (aom_codec_control(codec_ctx, AOME_GET_LOOPFILTER_LEVEL, &loop_filter_level) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to get loop filter level.\n");
    }

    if (Size < 4) return;
    int arnr_max_frames = Data[3] % 16; // ARNR max frames range
    if (aom_codec_control(codec_ctx, AOME_SET_ARNR_MAXFRAMES, arnr_max_frames) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set ARNR max frames.\n");
    }

    if (Size < 5) return;
    int sharpness = Data[4] % 8; // Sharpness range
    if (aom_codec_control(codec_ctx, AOME_SET_SHARPNESS, sharpness) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set sharpness.\n");
    }
}

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();

    initialize_codec(&codec_ctx, iface);
    fuzz_codec_controls(&codec_ctx, Data, Size);
    cleanup_codec(&codec_ctx);

    return 0;
}