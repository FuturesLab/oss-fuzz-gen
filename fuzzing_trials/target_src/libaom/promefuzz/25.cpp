// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AOME_SET_SCALEMODE at aomcx.h:1904:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS at aomcx.h:1943:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_TUNING at aomcx.h:1934:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID at aomcx.h:1907:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL at aomcx.h:2013:1 in aomcx.h
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
#include <cassert>
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

static void initialize_codec_context(aom_codec_ctx_t &ctx) {
    memset(&ctx, 0, sizeof(ctx));
    ctx.name = "dummy_codec";
    ctx.iface = nullptr; // Assume a valid interface is assigned in real use
    ctx.err = static_cast<aom_codec_err_t>(0);
    ctx.init_flags = 0;
    ctx.priv = nullptr;
}

static void fuzz_aom_codec_control_typechecked_AOME_SET_SCALEMODE(aom_codec_ctx_t &ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_scaling_mode_t)) return;
    aom_scaling_mode_t scale_mode;
    memcpy(&scale_mode, Data, sizeof(scale_mode));
    aom_codec_control_typechecked_AOME_SET_SCALEMODE(&ctx, AOME_SET_SCALEMODE, &scale_mode);
}

static void fuzz_aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS(aom_codec_ctx_t &ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int num_layers;
    memcpy(&num_layers, Data, sizeof(num_layers));
    aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS(&ctx, AOME_SET_NUMBER_SPATIAL_LAYERS, num_layers);
}

static void fuzz_aom_codec_control_typechecked_AOME_SET_TUNING(aom_codec_ctx_t &ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int tuning;
    memcpy(&tuning, Data, sizeof(tuning));
    aom_codec_control_typechecked_AOME_SET_TUNING(&ctx, AOME_SET_TUNING, tuning);
}

static void fuzz_aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID(aom_codec_ctx_t &ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int layer_id;
    memcpy(&layer_id, Data, sizeof(layer_id));
    aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID(&ctx, AOME_SET_SPATIAL_LAYER_ID, layer_id);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL(aom_codec_ctx_t &ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int max_gf_interval;
    memcpy(&max_gf_interval, Data, sizeof(max_gf_interval));
    aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL(&ctx, AV1E_SET_MAX_GF_INTERVAL, max_gf_interval);
}

static void fuzz_aom_codec_control_typechecked_AOME_SET_ENABLEAUTOBWDREF(aom_codec_ctx_t &ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int enable_autobwdref;
    memcpy(&enable_autobwdref, Data, sizeof(enable_autobwdref));
    aom_codec_control_typechecked_AOME_SET_ENABLEAUTOBWDREF(&ctx, AOME_SET_ENABLEAUTOBWDREF, enable_autobwdref);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    initialize_codec_context(codec_ctx);

    fuzz_aom_codec_control_typechecked_AOME_SET_SCALEMODE(codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS(codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AOME_SET_TUNING(codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID(codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL(codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AOME_SET_ENABLEAUTOBWDREF(codec_ctx, Data, Size);

    return 0;
}