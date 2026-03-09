// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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
#include "aomcx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom_frame_buffer.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return 0;

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.iface = aom_codec_av1_cx();

    unsigned int param = 0;
    memcpy(&param, Data, sizeof(unsigned int));

    // Test AV1E_SET_CDF_UPDATE_MODE
    aom_codec_control(&codec_ctx, AV1E_SET_CDF_UPDATE_MODE, param);

    // Test AV1E_SET_FP_MT_UNIT_TEST
    aom_codec_control(&codec_ctx, AV1E_SET_FP_MT_UNIT_TEST, param);

    // Test AV1E_SET_TILE_COLUMNS
    aom_codec_control(&codec_ctx, AV1E_SET_TILE_COLUMNS, param);

    // Test AV1E_SET_FORCE_VIDEO_MODE
    aom_codec_control(&codec_ctx, AV1E_SET_FORCE_VIDEO_MODE, param);

    // Test AV1E_SET_MAX_GF_INTERVAL
    aom_codec_control(&codec_ctx, AV1E_SET_MAX_GF_INTERVAL, param);

    // Test AV1E_SET_FRAME_PARALLEL_DECODING
    aom_codec_control(&codec_ctx, AV1E_SET_FRAME_PARALLEL_DECODING, param);

    return 0;
}