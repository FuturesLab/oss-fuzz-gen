// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_QM at aomcx.h:2052:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE at aomcx.h:2043:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE at aomcx.h:1995:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0; // Ensure we have enough data

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get AV1 encoder interface
    aom_codec_err_t res;

    // Initialize codec context
    res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Prepare input data for fuzzing
    int control_value = *reinterpret_cast<const int*>(Data); // Use first 4 bytes as control value

    // Fuzz different API functions
    aom_codec_control_typechecked_AV1E_SET_ENABLE_QM(&codec_ctx, 0, control_value % 2); // Enable/Disable QM
    aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE(&codec_ctx, 0, control_value % 2); // Force video mode
    aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE(&codec_ctx, 0, control_value % 3); // Set CDF update mode
    aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec_ctx, 0, control_value % 2); // Enable/Disable OBMC
    aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(&codec_ctx, 0, control_value % 100); // Set min GF interval
    aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT(&codec_ctx, 0, control_value % 100); // Set max inter bitrate pct

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    return 0;
}