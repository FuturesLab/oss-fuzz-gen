// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA at aomcx.h:2290:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE at aomcx.h:1977:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY at aomcx.h:2170:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA at aomcx.h:2302:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS at aomcx.h:2338:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES at aomcx.h:2167:1 in aomcx.h
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
#include "aom/aom_codec.h"
#include "aom/aom_encoder.h"
#include "aom/aomcx.h"

static void initialize_codec_context(aom_codec_ctx_t &codec_ctx) {
    memset(&codec_ctx, 0, sizeof(aom_codec_ctx_t));
    codec_ctx.name = "AV1 Codec";
    codec_ctx.iface = aom_codec_av1_cx();
    codec_ctx.err = AOM_CODEC_OK;
}

static void cleanup_codec_context(aom_codec_ctx_t &codec_ctx) {
    aom_codec_destroy(&codec_ctx);
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    initialize_codec_context(codec_ctx);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA
    bool enable_diagonal_intra = Data[0] % 2;
    aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(&codec_ctx, AV1E_SET_ENABLE_DIAGONAL_INTRA, enable_diagonal_intra);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE
    bool enable_error_resilient = Data[0] % 2;
    aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(&codec_ctx, AV1E_SET_ERROR_RESILIENT_MODE, enable_error_resilient);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY
    bool enable_overlay = Data[0] % 2;
    aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(&codec_ctx, AV1E_SET_ENABLE_OVERLAY, enable_overlay);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA
    bool enable_directional_intra = Data[0] % 2;
    aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA(&codec_ctx, AV1E_SET_ENABLE_DIRECTIONAL_INTRA, enable_directional_intra);

    // Fuzz aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS
    int num_operating_points;
    aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS(&codec_ctx, AV1E_GET_NUM_OPERATING_POINTS, &num_operating_points);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES
    bool enable_superres = Data[0] % 2;
    aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES(&codec_ctx, AV1E_SET_ENABLE_SUPERRES, enable_superres);

    cleanup_codec_context(codec_ctx);
    return 0;
}