// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS at aomcx.h:2387:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING at aomcx.h:1971:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_CDEF at aomcx.h:2037:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING at aomcx.h:2341:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FP_MT at aomcx.h:2329:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT at aomcx.h:2049:1 in aomcx.h
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

static aom_codec_ctx_t *initialize_codec_context() {
    aom_codec_ctx_t *ctx = new aom_codec_ctx_t();
    memset(ctx, 0, sizeof(aom_codec_ctx_t));
    return ctx;
}

static void cleanup_codec_context(aom_codec_ctx_t *ctx) {
    if (ctx) {
        delete ctx;
    }
}

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0; // Ensure there's enough data

    aom_codec_ctx_t *codec_ctx = initialize_codec_context();
    if (!codec_ctx) return 0;

    // Extract control values from input data
    int enable_adaptive_sharpness = Data[0] % 2;
    int enable_keyframe_filtering = Data[1] % 2;
    int enable_cdef = Data[2] % 2;
    int skip_postproc_filtering = Data[3] % 2;
    int fp_mt = Data[4] % 2;
    int disable_trellis_quant = Data[5] % 2;

    // Invoke target API functions with extracted values
    aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS(codec_ctx, 0, enable_adaptive_sharpness);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING(codec_ctx, 0, enable_keyframe_filtering);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_CDEF(codec_ctx, 0, enable_cdef);
    aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING(codec_ctx, 0, skip_postproc_filtering);
    aom_codec_control_typechecked_AV1E_SET_FP_MT(codec_ctx, 0, fp_mt);
    aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT(codec_ctx, 0, disable_trellis_quant);

    cleanup_codec_context(codec_ctx);
    return 0;
}