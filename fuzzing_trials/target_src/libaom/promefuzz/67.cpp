// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST at aomcx.h:1986:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH at aomcx.h:2314:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ at aomcx.h:2293:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR at aomcx.h:2359:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING at aomcx.h:1971:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    codec_ctx.name = "av1";
    codec_ctx.err = AOM_CODEC_OK;
    codec_ctx.init_flags = 0;
    codec_ctx.priv = nullptr;

    int value = *reinterpret_cast<const int*>(Data);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST
    aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST(&codec_ctx, AV1E_SET_FRAME_PERIODIC_BOOST, static_cast<unsigned int>(value));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH
    aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH(&codec_ctx, AV1E_SET_DELTAQ_STRENGTH, static_cast<unsigned int>(value));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ
    aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ(&codec_ctx, AV1E_SET_DV_COST_UPD_FREQ, static_cast<unsigned int>(value));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR
    aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR(&codec_ctx, AV1E_SET_BITRATE_ONE_PASS_CBR, static_cast<unsigned int>(value));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING
    aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING(&codec_ctx, AV1E_SET_ENABLE_KEYFRAME_FILTERING, static_cast<unsigned int>(value));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC
    aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec_ctx, AV1E_SET_ENABLE_OBMC, static_cast<unsigned int>(value));

    // Cleanup if necessary
    if (codec_ctx.priv) {
        aom_codec_destroy(&codec_ctx);
    }

    return 0;
}