// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
#include <iostream>
#include <cstring>
#include <cstdint>
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

static aom_codec_ctx_t initialize_codec() {
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));
    codec.iface = aom_codec_av1_cx();
    codec.err = aom_codec_enc_init(&codec, codec.iface, nullptr, 0);
    return codec;
}

static void cleanup_codec(aom_codec_ctx_t &codec) {
    aom_codec_destroy(&codec);
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec = initialize_codec();
    if (codec.err != AOM_CODEC_OK) {
        return 0;
    }

    aom_codec_err_t res;
    uint32_t control_id = Data[0];
    int control_value = Size > 1 ? Data[1] : 0;

    switch (control_id % 6) {
        case 0:
            res = aom_codec_control(&codec, AOME_SET_ENABLEAUTOALTREF, control_value);
            break;
        case 1:
            res = aom_codec_control(&codec, AV1E_SET_FORCE_VIDEO_MODE, control_value);
            break;
        case 2:
            res = aom_codec_control(&codec, AV1E_SET_SVC_FRAME_DROP_MODE, control_value);
            break;
        case 3:
            res = aom_codec_control(&codec, AV1E_SET_ENABLE_QM, control_value);
            break;
        case 4:
            res = aom_codec_control(&codec, AV1E_SET_AUTO_INTRA_TOOLS_OFF, control_value);
            break;
        case 5:
            res = aom_codec_control(&codec, AV1E_SET_ENABLE_KEYFRAME_FILTERING, control_value);
            break;
        default:
            res = AOM_CODEC_INVALID_PARAM;
            break;
    }

    if (res != AOM_CODEC_OK) {
        std::cerr << "Codec control failed with error: " << res << std::endl;
    }

    cleanup_codec(codec);
    return 0;
}