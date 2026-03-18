// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_FP_MT_UNIT_TEST at aomcx.h:2332:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH at aomcx.h:2314:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_NOISE_SENSITIVITY at aomcx.h:1989:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TILE_COLUMNS at aomcx.h:1962:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF at aomcx.h:2323:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE at aomcx.h:1995:1 in aomcx.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cstring>
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomdx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_integer.h"
#include "aom_codec.h"
#include "aom_image.h"
#include "aom.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 2) return 0;

    // Create a dummy codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Prepare dummy input values from the fuzz data
    int control_id = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    unsigned int control_value = *reinterpret_cast<const unsigned int*>(Data);
    Data += sizeof(unsigned int);
    Size -= sizeof(unsigned int);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FP_MT_UNIT_TEST
    aom_codec_err_t res1 = aom_codec_control_typechecked_AV1E_SET_FP_MT_UNIT_TEST(&codec_ctx, control_id, control_value);
    if (res1 != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_FP_MT_UNIT_TEST: " << res1 << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH
    aom_codec_err_t res2 = aom_codec_control_typechecked_AV1E_SET_DELTAQ_STRENGTH(&codec_ctx, control_id, control_value);
    if (res2 != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_DELTAQ_STRENGTH: " << res2 << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_NOISE_SENSITIVITY
    aom_codec_err_t res3 = aom_codec_control_typechecked_AV1E_SET_NOISE_SENSITIVITY(&codec_ctx, control_id, control_value);
    if (res3 != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_NOISE_SENSITIVITY: " << res3 << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TILE_COLUMNS
    aom_codec_err_t res4 = aom_codec_control_typechecked_AV1E_SET_TILE_COLUMNS(&codec_ctx, control_id, control_value);
    if (res4 != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_TILE_COLUMNS: " << res4 << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF
    aom_codec_err_t res5 = aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF(&codec_ctx, control_id, control_value);
    if (res5 != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_AUTO_INTRA_TOOLS_OFF: " << res5 << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE
    aom_codec_err_t res6 = aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE(&codec_ctx, control_id, control_value);
    if (res6 != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_CDF_UPDATE_MODE: " << res6 << std::endl;
    }

    return 0;
}