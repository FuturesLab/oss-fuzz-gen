// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA at aomcx.h:2164:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE at aomcx.h:2019:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE at aomcx.h:1980:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS at aomcx.h:2338:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY at aomcx.h:2170:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA at aomcx.h:2290:1 in aomcx.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
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
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom_frame_buffer.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aomcx.h"
#include "aomdx.h"

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int enable_cfl_intra = Data[0] % 2; // Either 0 or 1
    aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA(codec, 0, enable_cfl_intra);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int color_range = Data[0] % 2; // Either 0 or 1
    aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE(codec, 0, color_range);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int s_frame_mode = Data[0] % 2; // Either 0 or 1
    aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE(codec, 0, s_frame_mode);
}

static void fuzz_aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS(aom_codec_ctx_t *codec) {
    int num_operating_points;
    aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS(codec, 0, &num_operating_points);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int enable_overlay = Data[0] % 2; // Either 0 or 1
    aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(codec, 0, enable_overlay);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int enable_diagonal_intra = Data[0] % 2; // Either 0 or 1
    aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(codec, 0, enable_diagonal_intra);
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    // Initialize codec context
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) return 0;

    // Initialize the codec
    if (aom_codec_enc_init(&codec, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz each function
    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS(&codec);
    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(&codec, Data, Size);

    // Cleanup
    aom_codec_destroy(&codec);

    return 0;
}