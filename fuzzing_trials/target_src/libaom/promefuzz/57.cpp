// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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
#include <aom/aom_integer.h>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_encoder.h>
#include <aom/aom_external_partition.h>
#include <aom/aom.h>
#include <aom/aom_decoder.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>
}

#include <cstdint>
#include <cstring>

static aom_codec_ctx_t initialize_codec_context() {
    aom_codec_ctx_t codec_ctx;
    std::memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.name = "av1";
    return codec_ctx;
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int enable_diagonal_intra = Data[0] % 2;
    aom_codec_control(codec_ctx, AV1E_SET_ENABLE_DIAGONAL_INTRA, enable_diagonal_intra);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int error_resilient_mode = Data[0] % 2;
    aom_codec_control(codec_ctx, AV1E_SET_ERROR_RESILIENT_MODE, error_resilient_mode);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int enable_overlay = Data[0] % 2;
    aom_codec_control(codec_ctx, AV1E_SET_ENABLE_OVERLAY, enable_overlay);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int color_range = Data[0];
    aom_codec_control(codec_ctx, AV1E_SET_COLOR_RANGE, color_range);
}

static void fuzz_aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS(aom_codec_ctx_t *codec_ctx) {
    int num_operating_points = 0;
    aom_codec_control(codec_ctx, AV1E_GET_NUM_OPERATING_POINTS, &num_operating_points);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    int transfer_characteristics = Data[0];
    aom_codec_control(codec_ctx, AV1E_SET_TRANSFER_CHARACTERISTICS, transfer_characteristics);
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx = initialize_codec_context();

    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS(&codec_ctx);
    fuzz_aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS(&codec_ctx, Data, Size);

    // Cleanup if necessary
    aom_codec_destroy(&codec_ctx);
    return 0;
}