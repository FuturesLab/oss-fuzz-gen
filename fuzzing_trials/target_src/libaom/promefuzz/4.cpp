// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION at aomcx.h:2007:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL at aomcx.h:2317:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL at aomcx.h:2390:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE at aomcx.h:1980:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX at aomcx.h:2025:1 in aomcx.h
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
#include "aom_encoder.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(int)) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.name = "AV1 Codec";
    codec_ctx.iface = aom_codec_av1_cx();
    codec_ctx.err = AOM_CODEC_OK;

    int control_value = 0;
    memcpy(&control_value, Data, sizeof(int));

    try {
        aom_codec_err_t res;

        // Fuzz aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES
        res = aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec_ctx, AV1E_SET_COLOR_PRIMARIES, control_value);
        if (res != AOM_CODEC_OK) {
            throw std::runtime_error("Error in AV1E_SET_COLOR_PRIMARIES");
        }

        // Fuzz aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION
        res = aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION(&codec_ctx, AV1E_SET_CHROMA_SAMPLE_POSITION, control_value);
        if (res != AOM_CODEC_OK) {
            throw std::runtime_error("Error in AV1E_SET_CHROMA_SAMPLE_POSITION");
        }

        // Fuzz aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL
        res = aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL(&codec_ctx, AV1E_SET_LOOPFILTER_CONTROL, control_value);
        if (res != AOM_CODEC_OK) {
            throw std::runtime_error("Error in AV1E_SET_LOOPFILTER_CONTROL");
        }

        // Fuzz aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL
        aom_rc_funcs_t rc_funcs;
        memset(&rc_funcs, 0, sizeof(rc_funcs));
        res = aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL(&codec_ctx, AV1E_SET_EXTERNAL_RATE_CONTROL, &rc_funcs);
        if (res != AOM_CODEC_OK) {
            throw std::runtime_error("Error in AV1E_SET_EXTERNAL_RATE_CONTROL");
        }

        // Fuzz aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE
        res = aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE(&codec_ctx, AV1E_SET_S_FRAME_MODE, control_value);
        if (res != AOM_CODEC_OK) {
            throw std::runtime_error("Error in AV1E_SET_S_FRAME_MODE");
        }

        // Fuzz aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX
        res = aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX(&codec_ctx, AV1E_SET_TARGET_SEQ_LEVEL_IDX, control_value);
        if (res != AOM_CODEC_OK) {
            throw std::runtime_error("Error in AV1E_SET_TARGET_SEQ_LEVEL_IDX");
        }
    } catch (const std::exception &e) {
        fprintf(stderr, "Exception: %s\n", e.what());
    }

    return 0;
}