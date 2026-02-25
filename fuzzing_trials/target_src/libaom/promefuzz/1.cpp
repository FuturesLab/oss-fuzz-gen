// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE at aomcx.h:2383:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH at aomcx.h:2305:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA at aomcx.h:2164:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL at aomcx.h:2317:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX at aomcx.h:2025:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA at aomcx.h:2290:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get AV1 encoder interface
    aom_codec_flags_t flags = 0; // Initialize with default flags

    // Initialize codec context
    if (aom_codec_enc_init(&codec_ctx, iface, nullptr, flags) != AOM_CODEC_OK) {
        return 0; // Initialization failed
    }

    int control_value = Data[0] % 2; // Control value for binary controls
    int seq_level_idx = Data[0] % 32; // Assuming 32 valid indices

    // Explore different function calls based on the input data
    switch (Data[0] % 6) {
        case 0:
            aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE(&codec_ctx, 0, control_value);
            break;
        case 1:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH(&codec_ctx, 0, control_value);
            break;
        case 2:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA(&codec_ctx, 0, control_value);
            break;
        case 3:
            aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL(&codec_ctx, 0, control_value);
            break;
        case 4:
            aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX(&codec_ctx, 0, seq_level_idx);
            break;
        case 5:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(&codec_ctx, 0, control_value);
            break;
    }

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    return 0;
}