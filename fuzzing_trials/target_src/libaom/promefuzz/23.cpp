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
#include <aom_codec.h>
#include <aom_encoder.h>
#include <aomcx.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void fuzz_aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST(aom_codec_ctx_t *codec, int value) {
    aom_codec_control(codec, AV1E_SET_FRAME_PERIODIC_BOOST, value);
}

static void fuzz_aom_codec_control_typechecked_AOME_SET_CPUUSED(aom_codec_ctx_t *codec, int value) {
    aom_codec_control(codec, AOME_SET_CPUUSED, value);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(aom_codec_ctx_t *codec, int value) {
    aom_codec_control(codec, AV1E_SET_MIN_GF_INTERVAL, value);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC(aom_codec_ctx_t *codec, int value) {
    aom_codec_control(codec, AV1E_SET_POSTENCODE_DROP_RTC, value);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING(aom_codec_ctx_t *codec, int value) {
    aom_codec_control(codec, AV1E_SET_FRAME_PARALLEL_DECODING, value);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES(aom_codec_ctx_t *codec, int value) {
    aom_codec_control(codec, AV1E_SET_ENABLE_SUPERRES, value);
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    int control_value = *reinterpret_cast<const int*>(Data);

    fuzz_aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST(&codec, control_value);
    fuzz_aom_codec_control_typechecked_AOME_SET_CPUUSED(&codec, control_value);
    fuzz_aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(&codec, control_value);
    fuzz_aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC(&codec, control_value);
    fuzz_aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING(&codec, control_value);
    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES(&codec, control_value);

    return 0;
}