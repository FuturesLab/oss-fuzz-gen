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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aomdx.h"

static void initialize_codec(aom_codec_ctx_t &codec_ctx, aom_codec_iface_t *iface) {
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0)) {
        fprintf(stderr, "Failed to get default codec config\n");
        exit(EXIT_FAILURE);
    }
    if (aom_codec_enc_init(&codec_ctx, iface, &cfg, 0)) {
        fprintf(stderr, "Failed to initialize codec\n");
        exit(EXIT_FAILURE);
    }
}

static void cleanup_codec(aom_codec_ctx_t &codec_ctx) {
    if (aom_codec_destroy(&codec_ctx)) {
        fprintf(stderr, "Failed to destroy codec\n");
        exit(EXIT_FAILURE);
    }
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();

    initialize_codec(codec_ctx, iface);

    int control_id = Data[0] % 6;
    int value = (Size > 1) ? Data[1] : 0;

    switch (control_id) {
        case 0:
            aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_OVERLAY, value);
            break;
        case 1:
            aom_codec_control(&codec_ctx, AV1E_SET_LOOPFILTER_CONTROL, value);
            break;
        case 2:
            aom_codec_control(&codec_ctx, AV1E_SET_COLOR_RANGE, value);
            break;
        case 3:
            aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_DIRECTIONAL_INTRA, value);
            break;
        case 4:
            int level;
            aom_codec_control(&codec_ctx, AOME_GET_LOOPFILTER_LEVEL, &level);
            break;
        case 5:
            aom_codec_control(&codec_ctx, AV1E_SET_TRANSFER_CHARACTERISTICS, value);
            break;
    }

    cleanup_codec(codec_ctx);
    return 0;
}