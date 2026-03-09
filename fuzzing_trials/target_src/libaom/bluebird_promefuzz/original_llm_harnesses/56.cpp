// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aomcx.h>
#include <aom/aom.h>

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Initialize codec context
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));
    codec.iface = aom_codec_av1_cx();

    // Prepare a dummy configuration
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(codec.iface, &cfg, 0)) {
        return 0;
    }

    // Initialize the codec
    if (aom_codec_enc_init(&codec, codec.iface, &cfg, 0)) {
        return 0;
    }

    // Extract a boolean and an integer from the input data
    bool enable = Data[0] % 2;
    int strength = *reinterpret_cast<const int *>(Data);

    // Call API functions with the extracted values
    aom_codec_control(&codec, AV1E_SET_ENABLE_CDEF, enable);
    aom_codec_control(&codec, AV1E_SET_DELTAQ_STRENGTH, strength);
    aom_codec_control(&codec, AV1E_SET_ENABLE_QM, enable);
    aom_codec_control(&codec, AV1E_ENABLE_SB_QP_SWEEP, enable);
    aom_codec_control(&codec, AV1E_SET_ENABLE_KEYFRAME_FILTERING, enable);
    aom_codec_control(&codec, AV1E_SET_FRAME_PARALLEL_DECODING, enable);

    // Cleanup codec context
    aom_codec_destroy(&codec);

    return 0;
}