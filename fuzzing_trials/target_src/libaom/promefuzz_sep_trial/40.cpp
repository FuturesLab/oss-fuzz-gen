// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_QM at aomcx.h:2052:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE at aomcx.h:1995:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL at aomcx.h:1968:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL at aomcx.h:2010:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT at aomcx.h:1948:1 in aomcx.h
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
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;  // Ensure there's enough data

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    
    // Initialize codec context
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get AV1 encoder interface
    if (aom_codec_enc_init(&codec_ctx, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;  // Initialization failed
    }

    // Prepare input data
    unsigned int qm_enable = Data[0] % 2;  // Randomly enable or disable QM
    unsigned int cdf_update_mode = Data[1] % 3;  // Random mode between 0 and 2
    unsigned int obmc_enable = Data[2] % 2;  // Randomly enable or disable OBMC
    unsigned int tpl_model_enable = Data[3] % 2;  // Randomly enable or disable TPL model
    unsigned int min_gf_interval = Data[4] % 32;  // Random minimum GF interval
    unsigned int max_inter_bitrate_pct = Data[5] % 100;  // Random percentage

    // Fuzzing the various codec control functions
    aom_codec_control_typechecked_AV1E_SET_ENABLE_QM(&codec_ctx, 0, qm_enable);
    aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE(&codec_ctx, 0, cdf_update_mode);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec_ctx, 0, obmc_enable);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL(&codec_ctx, 0, tpl_model_enable);
    aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(&codec_ctx, 0, min_gf_interval);
    aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT(&codec_ctx, 0, max_inter_bitrate_pct);

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    return 0;
}