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
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aomcx.h"
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom_integer.h"
}

#include <cstdint>
#include <cstring>
#include <cstdio>

static aom_codec_ctx_t initialize_codec() {
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_err_t res = aom_codec_enc_config_default(iface, &cfg, 0);
    if (res == AOM_CODEC_OK) {
        res = aom_codec_enc_init(&codec, iface, &cfg, 0);
    }
    if (res != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to initialize codec: %s\n", aom_codec_err_to_string(res));
    }
    return codec;
}

static void cleanup_codec(aom_codec_ctx_t &codec) {
    aom_codec_destroy(&codec);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec = initialize_codec();

    int control_id = Data[0] % 6;
    int param = *reinterpret_cast<const int*>(Data);

    aom_codec_err_t res;
    switch (control_id) {
        case 0:
            res = aom_codec_control(&codec, AV1E_SET_ENABLE_TPL_MODEL, param);
            break;
        case 1:
            res = aom_codec_control(&codec, AV1E_SET_BITRATE_ONE_PASS_CBR, param);
            break;
        case 2:
            res = aom_codec_control(&codec, AV1E_ENABLE_RATE_GUIDE_DELTAQ, param);
            break;
        case 3:
            res = aom_codec_control(&codec, AV1E_SET_SKIP_POSTPROC_FILTERING, param);
            break;
        case 4:
            res = aom_codec_control(&codec, AV1E_SET_AUTO_TILES, param);
            break;
        case 5:
            res = aom_codec_control(&codec, AV1E_SET_AQ_MODE, param);
            break;
        default:
            res = AOM_CODEC_INVALID_PARAM;
            break;
    }

    if (res != AOM_CODEC_OK) {
        fprintf(stderr, "Codec control failed: %s\n", aom_codec_err_to_string(res));
    }

    cleanup_codec(codec);
    return 0;
}