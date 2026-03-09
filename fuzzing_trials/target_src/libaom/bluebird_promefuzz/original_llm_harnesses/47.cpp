// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    int value;
    memcpy(&value, Data, sizeof(int));

    // 1. Test aom_codec_control_typechecked_AOME_SET_CQ_LEVEL
    aom_codec_control(&codec, AOME_SET_CQ_LEVEL, value);

    // 2. Test aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER_64
    int64_t last_quantizer_64;
    aom_codec_control(&codec, AOME_GET_LAST_QUANTIZER_64, &last_quantizer_64);

    // 3. Test aom_codec_control_typechecked_AOME_SET_ARNR_STRENGTH
    aom_codec_control(&codec, AOME_SET_ARNR_STRENGTH, value);

    // 4. Test aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT
    // Assuming correct macro name is AOME_SET_MAX_INTER_BITRATE_PCT
    #ifdef AOME_SET_MAX_INTER_BITRATE_PCT
    aom_codec_control(&codec, AOME_SET_MAX_INTER_BITRATE_PCT, value);
    #endif

    // 5. Test aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER
    int last_quantizer;
    aom_codec_control(&codec, AOME_GET_LAST_QUANTIZER, &last_quantizer);

    // 6. Test aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD
    aom_codec_control(&codec, AOME_SET_STATIC_THRESHOLD, value);

    // Cleanup
    aom_codec_destroy(&codec);

    return 0;
}