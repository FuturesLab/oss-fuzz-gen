// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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

static void initialize_codec(aom_codec_ctx_t &codec, aom_codec_iface_t *iface) {
    aom_codec_err_t res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        // Handle codec initialization error
    }
}

static void cleanup_codec(aom_codec_ctx_t &codec) {
    aom_codec_err_t res = aom_codec_destroy(&codec);
    if (res != AOM_CODEC_OK) {
        // Handle codec destruction error
    }
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + 1) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    initialize_codec(codec, iface);

    int control_id = Data[0] % 6;
    const int *param = reinterpret_cast<const int*>(Data + 1);

    switch (control_id) {
        case 0:
            aom_codec_control(&codec, AV1E_SET_FORCE_VIDEO_MODE, *param);
            break;
        case 1:
            aom_codec_control(&codec, AV1E_SET_ENABLE_QM, *param);
            break;
        case 2:
            aom_codec_control(&codec, AV1E_SET_AUTO_INTRA_TOOLS_OFF, *param);
            break;
        case 3:
            aom_codec_control(&codec, AV1E_SET_TILE_COLUMNS, *param);
            break;
        case 4:
            aom_codec_control(&codec, AV1E_SET_FRAME_PARALLEL_DECODING, *param);
            break;
        case 5:
            aom_codec_control(&codec, AV1E_SET_ENABLE_OBMC, *param);
            break;
        default:
            break;
    }

    cleanup_codec(codec);
    return 0;
}