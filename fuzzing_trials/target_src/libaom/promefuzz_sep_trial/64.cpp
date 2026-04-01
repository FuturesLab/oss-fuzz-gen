// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE at aomcx.h:1977:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT at aomcx.h:1992:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL at aomcx.h:2317:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE at aomcx.h:2022:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_SEQ_LEVEL_IDX at aomcx.h:2028:1 in aomcx.h
// aom_codec_control_typechecked_AOME_GET_LOOPFILTER_LEVEL at aomcx.h:2320:1 in aomcx.h
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
#include <exception>
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

static void fuzz_AV1E_SET_ERROR_RESILIENT_MODE(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int mode = *reinterpret_cast<const int *>(Data);
    aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(ctx, 0, mode);
}

static void fuzz_AV1E_SET_TUNE_CONTENT(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int content_type = *reinterpret_cast<const int *>(Data);
    aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT(ctx, 0, content_type);
}

static void fuzz_AV1E_SET_LOOPFILTER_CONTROL(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int loopfilter_control = *reinterpret_cast<const int *>(Data);
    aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL(ctx, 0, loopfilter_control);
}

static void fuzz_AV1E_SET_RENDER_SIZE(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int)) return;
    int dimensions[2];
    dimensions[0] = *reinterpret_cast<const int *>(Data);
    dimensions[1] = *reinterpret_cast<const int *>(Data + sizeof(int));
    aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE(ctx, 0, dimensions);
}

static void fuzz_AV1E_GET_SEQ_LEVEL_IDX(aom_codec_ctx_t *ctx) {
    int seq_level_idx;
    aom_codec_control_typechecked_AV1E_GET_SEQ_LEVEL_IDX(ctx, 0, &seq_level_idx);
}

static void fuzz_AOME_GET_LOOPFILTER_LEVEL(aom_codec_ctx_t *ctx) {
    int loopfilter_level;
    aom_codec_control_typechecked_AOME_GET_LOOPFILTER_LEVEL(ctx, 0, &loopfilter_level);
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    try {
        fuzz_AV1E_SET_ERROR_RESILIENT_MODE(&codec_ctx, Data, Size);
        fuzz_AV1E_SET_TUNE_CONTENT(&codec_ctx, Data, Size);
        fuzz_AV1E_SET_LOOPFILTER_CONTROL(&codec_ctx, Data, Size);
        fuzz_AV1E_SET_RENDER_SIZE(&codec_ctx, Data, Size);
        fuzz_AV1E_GET_SEQ_LEVEL_IDX(&codec_ctx);
        fuzz_AOME_GET_LOOPFILTER_LEVEL(&codec_ctx);
    } catch (const std::exception &e) {
        fprintf(stderr, "Exception caught: %s\n", e.what());
    }

    return 0;
}