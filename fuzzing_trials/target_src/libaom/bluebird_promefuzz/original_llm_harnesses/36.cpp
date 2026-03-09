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
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    int control_id = 0;
    memcpy(&control_id, Data, sizeof(int));
    Data += sizeof(int);
    Size -= sizeof(int);

    switch (control_id) {
        case 0: {
            if (Size < sizeof(unsigned int)) break;
            unsigned int enable = 0;
            memcpy(&enable, Data, sizeof(unsigned int));
            aom_codec_control(&codec, AOME_SET_ENABLEAUTOALTREF, enable);
            break;
        }
        case 1: {
            if (Size < sizeof(int)) break;
            int max_consec_frame_drop = 0;
            memcpy(&max_consec_frame_drop, Data, sizeof(int));
            aom_codec_control(&codec, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, max_consec_frame_drop);
            break;
        }
        case 2: {
            if (Size < sizeof(unsigned int)) break;
            unsigned int force_video_mode = 0;
            memcpy(&force_video_mode, Data, sizeof(unsigned int));
            aom_codec_control(&codec, AV1E_SET_FORCE_VIDEO_MODE, force_video_mode);
            break;
        }
        case 3: {
            if (Size < sizeof(unsigned int)) break;
            unsigned int enable_rate_guide_deltaq = 0;
            memcpy(&enable_rate_guide_deltaq, Data, sizeof(unsigned int));
            aom_codec_control(&codec, AV1E_ENABLE_RATE_GUIDE_DELTAQ, enable_rate_guide_deltaq);
            break;
        }
        case 4: {
            if (Size < sizeof(unsigned int)) break;
            unsigned int bitrate_one_pass_cbr = 0;
            memcpy(&bitrate_one_pass_cbr, Data, sizeof(unsigned int));
            aom_codec_control(&codec, AV1E_SET_BITRATE_ONE_PASS_CBR, bitrate_one_pass_cbr);
            break;
        }
        case 5: {
            if (Size < sizeof(unsigned int)) break;
            unsigned int max_intra_bitrate_pct = 0;
            memcpy(&max_intra_bitrate_pct, Data, sizeof(unsigned int));
            aom_codec_control(&codec, AOME_SET_MAX_INTRA_BITRATE_PCT, max_intra_bitrate_pct);
            break;
        }
        default:
            break;
    }

    aom_codec_destroy(&codec);
    return 0;
}