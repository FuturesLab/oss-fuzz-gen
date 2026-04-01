// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
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
extern "C" {
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>
#include <aom/aom_integer.h>
#include <aom/aom_image.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_external_partition.h>
#include <aom/aom.h>
#include <aom/aom_decoder.h>
}

#include <cstdint>
#include <cstdlib>

static void fuzz_aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int mode = *reinterpret_cast<const unsigned int*>(Data);
    aom_codec_control(codec, AV1E_SET_SVC_FRAME_DROP_MODE, mode);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int strength = *reinterpret_cast<const unsigned int*>(Data);
    aom_codec_control(codec, AV1E_SET_DELTAQ_STRENGTH, strength);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_TILE_ROWS(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int tile_rows = *reinterpret_cast<const unsigned int*>(Data);
    aom_codec_control(codec, AV1E_SET_TILE_ROWS, tile_rows);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_FP_MT_UNIT_TEST(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int test_value = *reinterpret_cast<const unsigned int*>(Data);
    aom_codec_control(codec, AV1E_SET_FP_MT_UNIT_TEST, test_value);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int value = *reinterpret_cast<const unsigned int*>(Data);
    aom_codec_control(codec, AV1E_SET_AUTO_INTRA_TOOLS_OFF, value);
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int enable = *reinterpret_cast<const unsigned int*>(Data);
    aom_codec_control(codec, AV1E_SET_FRAME_PARALLEL_DECODING, enable);
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;

    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    if (aom_codec_enc_init(&codec, iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    fuzz_aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_TILE_ROWS(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_FP_MT_UNIT_TEST(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF(&codec, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING(&codec, Data, Size);

    aom_codec_destroy(&codec);
    return 0;
}