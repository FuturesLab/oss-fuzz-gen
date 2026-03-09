// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING at aomcx.h:1971:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ at aomcx.h:2293:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT at aomcx.h:2049:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR at aomcx.h:2359:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AQ_MODE at aomcx.h:1983:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AUTO_TILES at aomcx.h:2368:1 in aomcx.h
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
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aomcx.h"
#include "aomdx.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_integer.h"

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(unsigned int)) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize codec interface
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) return 0;

    // Initialize codec
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Prepare dummy data
    int param = *reinterpret_cast<const int*>(Data);
    unsigned int unsigned_param = *reinterpret_cast<const unsigned int*>(Data + sizeof(int));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING
    aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING(&codec_ctx, param, unsigned_param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ
    aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ(&codec_ctx, param, unsigned_param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT
    aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT(&codec_ctx, param, unsigned_param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR
    aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR(&codec_ctx, param, unsigned_param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_AQ_MODE
    aom_codec_control_typechecked_AV1E_SET_AQ_MODE(&codec_ctx, param, unsigned_param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_AUTO_TILES
    aom_codec_control_typechecked_AV1E_SET_AUTO_TILES(&codec_ctx, param, unsigned_param);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}