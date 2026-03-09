// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE at aomcx.h:1977:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT at aomcx.h:1992:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC at aomcx.h:2371:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE at aomcx.h:2022:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS at aomcx.h:2004:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA at aomcx.h:2302:1 in aomcx.h
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
#include <iostream>
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomdx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_integer.h"
#include "aom_codec.h"
#include "aom_image.h"
#include "aom.h"
#include "aomcx.h"

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int mode = 0;
    memcpy(&mode, Data, sizeof(int));
    aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(codec_ctx, 0, mode);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int content_type = 0;
    memcpy(&content_type, Data, sizeof(int));
    aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT(codec_ctx, 0, content_type);
}

static void fuzz_aom_codec_control_typechecked_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC(aom_codec_ctx_t *codec_ctx) {
    int high_motion_content = 0;
    aom_codec_control_typechecked_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC(codec_ctx, 0, &high_motion_content);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int)) return;
    int width = 0, height = 0;
    memcpy(&width, Data, sizeof(int));
    memcpy(&height, Data + sizeof(int), sizeof(int));
    int dimensions[2] = {width, height};
    aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE(codec_ctx, 0, dimensions);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int coefficients = 0;
    memcpy(&coefficients, Data, sizeof(int));
    aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS(codec_ctx, 0, coefficients);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int enable = 0;
    memcpy(&enable, Data, sizeof(int));
    aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA(codec_ctx, 0, enable);
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    fuzz_aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC(&codec_ctx);
    fuzz_aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA(&codec_ctx, Data, Size);

    return 0;
}