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
extern "C" {
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
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void fuzz_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int max_drop_ms = *reinterpret_cast<const int*>(Data);
    aom_codec_control(codec, AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR, max_drop_ms);
}

static void fuzz_AOME_SET_TUNING(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int tuning = *reinterpret_cast<const int*>(Data);
    aom_codec_control(codec, AOME_SET_TUNING, tuning);
}

static void fuzz_AOME_USE_REFERENCE(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int reference_frame = *reinterpret_cast<const int*>(Data);
    aom_codec_control(codec, AOME_USE_REFERENCE, reference_frame);
}

static void fuzz_AV1E_SET_SVC_REF_FRAME_CONFIG(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_svc_ref_frame_config_t)) return;
    aom_svc_ref_frame_config_t config;
    memcpy(&config, Data, sizeof(aom_svc_ref_frame_config_t));
    aom_codec_control(codec, AV1E_SET_SVC_REF_FRAME_CONFIG, &config);
}

static void fuzz_AV1E_SET_ENABLE_KEYFRAME_FILTERING(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int enable_filtering = *reinterpret_cast<const unsigned int*>(Data);
    aom_codec_control(codec, AV1E_SET_ENABLE_KEYFRAME_FILTERING, enable_filtering);
}

static void fuzz_AOME_SET_ENABLEAUTOBWDREF(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int enable_autobwdref = *reinterpret_cast<const int*>(Data);
    aom_codec_control(codec, AOME_SET_ENABLEAUTOBWDREF, enable_autobwdref);
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t)) return 0;

    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    fuzz_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR(&codec, Data, Size);
    fuzz_AOME_SET_TUNING(&codec, Data, Size);
    fuzz_AOME_USE_REFERENCE(&codec, Data, Size);
    fuzz_AV1E_SET_SVC_REF_FRAME_CONFIG(&codec, Data, Size);
    fuzz_AV1E_SET_ENABLE_KEYFRAME_FILTERING(&codec, Data, Size);
    fuzz_AOME_SET_ENABLEAUTOBWDREF(&codec, Data, Size);

    return 0;
}