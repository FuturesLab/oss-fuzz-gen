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
#include "aom/aom.h"
#include "aom/aom_encoder.h"
#include "aom/aom_codec.h"
#include "aom/aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;

    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    if (aom_codec_enc_init(&codec, iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    int control_id = 0;
    if (Size >= sizeof(int)) {
        memcpy(&control_id, Data, sizeof(int));
    }

    switch (control_id % 6) {
        case 0:
            if (Size >= sizeof(int) * 2) {
                unsigned int noise_sensitivity;
                memcpy(&noise_sensitivity, Data + sizeof(int), sizeof(unsigned int));
                aom_codec_control(&codec, AV1E_SET_NOISE_SENSITIVITY, noise_sensitivity);
            }
            break;
        case 1:
            if (Size >= sizeof(int) * 2) {
                unsigned int fp_mt_unit_test;
                memcpy(&fp_mt_unit_test, Data + sizeof(int), sizeof(unsigned int));
                aom_codec_control(&codec, AV1E_SET_FP_MT_UNIT_TEST, fp_mt_unit_test);
            }
            break;
        case 2:
            {
                unsigned int auto_intra_tools_off = 1;
                aom_codec_control(&codec, AV1E_SET_AUTO_INTRA_TOOLS_OFF, auto_intra_tools_off);
            }
            break;
        case 3:
            if (Size >= sizeof(int) * 2) {
                unsigned int tile_columns;
                memcpy(&tile_columns, Data + sizeof(int), sizeof(unsigned int));
                aom_codec_control(&codec, AV1E_SET_TILE_COLUMNS, tile_columns);
            }
            break;
        case 4:
            if (Size >= sizeof(int) * 2) {
                unsigned int frame_parallel_decoding;
                memcpy(&frame_parallel_decoding, Data + sizeof(int), sizeof(unsigned int));
                aom_codec_control(&codec, AV1E_SET_FRAME_PARALLEL_DECODING, frame_parallel_decoding);
            }
            break;
        case 5:
            if (Size >= sizeof(int) * 2) {
                unsigned int cdf_update_mode;
                memcpy(&cdf_update_mode, Data + sizeof(int), sizeof(unsigned int));
                aom_codec_control(&codec, AV1E_SET_CDF_UPDATE_MODE, cdf_update_mode);
            }
            break;
        default:
            break;
    }

    aom_codec_destroy(&codec);
    return 0;
}