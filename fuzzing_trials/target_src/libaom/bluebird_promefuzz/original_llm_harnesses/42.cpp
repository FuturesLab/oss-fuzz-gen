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
#include <cstring>
#include <cstdint>
#include <cstddef>
extern "C" {
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
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    unsigned int param = *reinterpret_cast<const unsigned int*>(Data);

    // Test AV1E_SET_AUTO_TILES
    aom_codec_control(&codec, AV1E_SET_AUTO_TILES, param);

    // Test AV1E_SET_SVC_FRAME_DROP_MODE
    aom_codec_control(&codec, AV1E_SET_SVC_FRAME_DROP_MODE, param);

    // Test AV1E_SET_ENABLE_TPL_MODEL
    aom_codec_control(&codec, AV1E_SET_ENABLE_TPL_MODEL, param);

    // Test AV1E_SET_TILE_ROWS
    aom_codec_control(&codec, AV1E_SET_TILE_ROWS, param);

    // Test AV1E_SET_ENABLE_RESTORATION
    aom_codec_control(&codec, AV1E_SET_ENABLE_RESTORATION, param);

    // Test AV1E_SET_CDF_UPDATE_MODE
    aom_codec_control(&codec, AV1E_SET_CDF_UPDATE_MODE, param);

    aom_codec_destroy(&codec);

    return 0;
}