// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL at aomcx.h:2013:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF at aomcx.h:1913:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE at aomcx.h:2022:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_SCALEMODE at aomcx.h:1904:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS at aomcx.h:1943:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ENABLEAUTOBWDREF at aomcx.h:2034:1 in aomcx.h
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
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"

static aom_codec_ctx_t initialize_codec() {
    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0)) {
        fprintf(stderr, "Failed to get default codec config.\n");
        exit(EXIT_FAILURE);
    }
    if (aom_codec_enc_init(&codec, iface, &cfg, 0)) {
        fprintf(stderr, "Failed to initialize codec.\n");
        exit(EXIT_FAILURE);
    }
    return codec;
}

static void cleanup_codec(aom_codec_ctx_t &codec) {
    if (aom_codec_destroy(&codec)) {
        fprintf(stderr, "Failed to destroy codec.\n");
    }
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec = initialize_codec();

    int random_value;
    memcpy(&random_value, Data, sizeof(int));

    // Test aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL
    aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL(&codec, 0, random_value);

    // Test aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF
    aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF(&codec, 0, random_value % 2);

    // Test aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE
    if (Size >= sizeof(int) + 2 * sizeof(int)) {
        int dimensions[2];
        memcpy(dimensions, Data + sizeof(int), 2 * sizeof(int));
        aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE(&codec, 0, dimensions);
    }

    // Test aom_codec_control_typechecked_AOME_SET_SCALEMODE
    if (Size >= sizeof(int) + 3 * sizeof(int)) {
        aom_scaling_mode_t scale_mode;
        scale_mode.h_scaling_mode = static_cast<AOM_SCALING_MODE>(random_value % 9);
        aom_codec_control_typechecked_AOME_SET_SCALEMODE(&codec, 0, &scale_mode);
    }

    // Test aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS
    aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS(&codec, 0, random_value % 4);

    // Test aom_codec_control_typechecked_AOME_SET_ENABLEAUTOBWDREF
    aom_codec_control_typechecked_AOME_SET_ENABLEAUTOBWDREF(&codec, 0, random_value % 2);

    cleanup_codec(codec);
    return 0;
}