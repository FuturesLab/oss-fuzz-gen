// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_ENABLE_LOW_COMPLEXITY_DECODE at aomcx.h:2380:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FP_MT at aomcx.h:2329:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING at aomcx.h:2341:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TILE_ROWS at aomcx.h:1965:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT at aomcx.h:2049:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    int control_value = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    aom_codec_ctx_t codec_ctx;
    codec_ctx.name = "test_codec";
    codec_ctx.iface = nullptr;
    codec_ctx.err = AOM_CODEC_OK;
    codec_ctx.init_flags = 0;
    codec_ctx.config.enc = nullptr;
    codec_ctx.priv = nullptr;

    aom_codec_err_t res;

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_LOW_COMPLEXITY_DECODE
    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_LOW_COMPLEXITY_DECODE(&codec_ctx, AV1E_SET_ENABLE_LOW_COMPLEXITY_DECODE, control_value);
    if (res != AOM_CODEC_OK) {
        // Handle error
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FP_MT
    res = aom_codec_control_typechecked_AV1E_SET_FP_MT(&codec_ctx, AV1E_SET_FP_MT, control_value);
    if (res != AOM_CODEC_OK) {
        // Handle error
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING
    res = aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING(&codec_ctx, AV1E_SET_SKIP_POSTPROC_FILTERING, control_value);
    if (res != AOM_CODEC_OK) {
        // Handle error
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TILE_ROWS
    res = aom_codec_control_typechecked_AV1E_SET_TILE_ROWS(&codec_ctx, AV1E_SET_TILE_ROWS, control_value);
    if (res != AOM_CODEC_OK) {
        // Handle error
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT
    res = aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT(&codec_ctx, AV1E_SET_DISABLE_TRELLIS_QUANT, control_value);
    if (res != AOM_CODEC_OK) {
        // Handle error
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC
    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec_ctx, AV1E_SET_ENABLE_OBMC, control_value);
    if (res != AOM_CODEC_OK) {
        // Handle error
    }

    return 0;
}