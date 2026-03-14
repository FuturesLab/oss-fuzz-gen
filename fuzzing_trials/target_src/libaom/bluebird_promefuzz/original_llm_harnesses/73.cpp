// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
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

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    int cq_level = *reinterpret_cast<const int *>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Set constant quality level
    aom_codec_err_t res = aom_codec_control(&codec_ctx, AOME_SET_CQ_LEVEL, cq_level);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Get last quantizer 64
    int64_t last_quantizer_64;
    res = aom_codec_control(&codec_ctx, AOME_GET_LAST_QUANTIZER_64, &last_quantizer_64);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Get last quantizer
    int last_quantizer;
    res = aom_codec_control(&codec_ctx, AOME_GET_LAST_QUANTIZER, &last_quantizer);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    if (Size < sizeof(int)) return 0;

    int static_threshold = *reinterpret_cast<const int *>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Set static threshold
    res = aom_codec_control(&codec_ctx, AOME_SET_STATIC_THRESHOLD, static_threshold);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    if (Size < sizeof(int)) return 0;

    int max_intra_bitrate_pct = *reinterpret_cast<const int *>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Set max intra bitrate percentage
    res = aom_codec_control(&codec_ctx, AOME_SET_MAX_INTRA_BITRATE_PCT, max_intra_bitrate_pct);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    if (Size < sizeof(int)) return 0;

    int arnr_maxframes = *reinterpret_cast<const int *>(Data);

    // Set ARNR max frames
    res = aom_codec_control(&codec_ctx, AOME_SET_ARNR_MAXFRAMES, arnr_maxframes);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    return 0;
}