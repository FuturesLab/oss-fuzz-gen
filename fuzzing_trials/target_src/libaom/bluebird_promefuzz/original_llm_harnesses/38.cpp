// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
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
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aomcx.h>
#include <aom/aom_external_partition.h>
#include <aom/aom.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void fuzz_codec_control_AV1E_SET_COLOR_PRIMARIES(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int color_primaries = *reinterpret_cast<const int *>(Data);
    aom_codec_control(ctx, AV1E_SET_COLOR_PRIMARIES, color_primaries);
}

static void fuzz_codec_control_AV1E_SET_TUNE_CONTENT(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int tune_content = *reinterpret_cast<const int *>(Data);
    aom_codec_control(ctx, AV1E_SET_TUNE_CONTENT, tune_content);
}

static void fuzz_codec_control_AV1E_SET_EXTERNAL_PARTITION(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_ext_part_funcs_t)) return;
    aom_ext_part_funcs_t ext_part_funcs;
    memcpy(&ext_part_funcs, Data, sizeof(aom_ext_part_funcs_t));
    aom_codec_control(ctx, AV1E_SET_EXTERNAL_PARTITION, &ext_part_funcs);
}

static void fuzz_codec_control_AV1E_SET_MATRIX_COEFFICIENTS(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int matrix_coefficients = *reinterpret_cast<const int *>(Data);
    aom_codec_control(ctx, AV1E_SET_MATRIX_COEFFICIENTS, matrix_coefficients);
}

static void fuzz_codec_control_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC(aom_codec_ctx_t *ctx) {
    int high_motion_content_screen_rtc;
    aom_codec_control(ctx, AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC, &high_motion_content_screen_rtc);
}

static void fuzz_codec_control_AV1E_SET_RENDER_SIZE(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int)) return;
    int width = *reinterpret_cast<const int *>(Data);
    int height = *reinterpret_cast<const int *>(Data + sizeof(int));
    aom_codec_control(ctx, AV1E_SET_RENDER_SIZE, width, height);
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.iface = aom_codec_av1_cx();

    // Initialize codec context
    if (aom_codec_enc_init(&codec_ctx, codec_ctx.iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz different control functions
    fuzz_codec_control_AV1E_SET_COLOR_PRIMARIES(&codec_ctx, Data, Size);
    fuzz_codec_control_AV1E_SET_TUNE_CONTENT(&codec_ctx, Data, Size);
    fuzz_codec_control_AV1E_SET_EXTERNAL_PARTITION(&codec_ctx, Data, Size);
    fuzz_codec_control_AV1E_SET_MATRIX_COEFFICIENTS(&codec_ctx, Data, Size);
    fuzz_codec_control_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC(&codec_ctx);
    fuzz_codec_control_AV1E_SET_RENDER_SIZE(&codec_ctx, Data, Size);

    // Clean up
    aom_codec_destroy(&codec_ctx);

    return 0;
}