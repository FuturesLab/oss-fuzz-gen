// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
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
#include <aom/aom_integer.h>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_encoder.h>
#include <aom/aom_external_partition.h>
#include <aom/aom.h>
#include <aom/aom_decoder.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    int value = *reinterpret_cast<const int*>(Data);

    // Fuzz aom_codec_control_typechecked_AOME_SET_CQ_LEVEL
    aom_codec_control(&codec, AOME_SET_CQ_LEVEL, value);

    // Fuzz aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF
    aom_codec_control(&codec, AOME_SET_ENABLEAUTOALTREF, value);

    // Fuzz aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS
    aom_codec_control(&codec, AOME_SET_NUMBER_SPATIAL_LAYERS, value);

    // Fuzz aom_codec_control_typechecked_AOME_GET_LOOPFILTER_LEVEL
    int loopfilter_level;
    aom_codec_control(&codec, AOME_GET_LOOPFILTER_LEVEL, &loopfilter_level);

    // Fuzz aom_codec_control_typechecked_AOME_SET_ARNR_MAXFRAMES
    aom_codec_control(&codec, AOME_SET_ARNR_MAXFRAMES, value);

    // Fuzz aom_codec_control_typechecked_AOME_SET_SHARPNESS
    aom_codec_control(&codec, AOME_SET_SHARPNESS, value);

    aom_codec_destroy(&codec);
    return 0;
}