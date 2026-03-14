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
#include "aom/aomdx.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aomcx.h"
#include "/src/aom/aom/aom_integer.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom.h"
#include "aom/aom_decoder.h"
}

#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>

static void InitializeCodecContext(aom_codec_ctx_t &ctx) {
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        std::cerr << "Failed to get default encoder configuration" << std::endl;
        return;
    }
    if (aom_codec_enc_init(&ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        std::cerr << "Failed to initialize encoder" << std::endl;
        return;
    }
}

static void CleanupCodecContext(aom_codec_ctx_t &ctx) {
    if (aom_codec_destroy(&ctx) != AOM_CODEC_OK) {
        std::cerr << "Failed to destroy codec context" << std::endl;
    }
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec_ctx;
    InitializeCodecContext(codec_ctx);

    int param_value = 0;
    std::memcpy(&param_value, Data, sizeof(int));

    // Fuzz aom_codec_control_typechecked_AOME_SET_TUNING
    aom_codec_control_typechecked_AOME_SET_TUNING(&codec_ctx, AOME_SET_TUNING, param_value);

    // Fuzz aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD
    aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD(&codec_ctx, AOME_SET_STATIC_THRESHOLD, static_cast<unsigned int>(param_value));

    // Fuzz aom_codec_control_typechecked_AOME_SET_ARNR_MAXFRAMES
    aom_codec_control_typechecked_AOME_SET_ARNR_MAXFRAMES(&codec_ctx, AOME_SET_ARNR_MAXFRAMES, static_cast<unsigned int>(param_value));

    // Fuzz aom_codec_control_typechecked_AOME_SET_ARNR_STRENGTH
    aom_codec_control_typechecked_AOME_SET_ARNR_STRENGTH(&codec_ctx, AOME_SET_ARNR_STRENGTH, static_cast<unsigned int>(param_value));

    // Fuzz aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF
    aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF(&codec_ctx, AOME_SET_ENABLEAUTOALTREF, static_cast<unsigned int>(param_value));

    // Fuzz aom_codec_control_typechecked_AOME_SET_CQ_LEVEL
    aom_codec_control_typechecked_AOME_SET_CQ_LEVEL(&codec_ctx, AOME_SET_CQ_LEVEL, param_value);

    CleanupCodecContext(codec_ctx);
    return 0;
}