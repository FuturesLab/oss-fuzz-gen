// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
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
#include <cstdint>
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

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res;

    // Initialize the codec context
    res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Use a portion of Data to set control parameters
    uint32_t control_value = 0;
    if (Size >= sizeof(uint32_t)) {
        memcpy(&control_value, Data, sizeof(uint32_t));
    }

    // Fuzz various control functions
    aom_codec_control(&codec_ctx, AOME_SET_CQ_LEVEL, control_value);
    aom_codec_control(&codec_ctx, AV1E_SET_COLOR_RANGE, control_value);
    aom_codec_control(&codec_ctx, AV1E_SET_FORCE_VIDEO_MODE, control_value);

    // Attempt to retrieve values
    int quantizer_64 = 0;
    int quantizer = 0;
    int num_operating_points = 0;

    aom_codec_control(&codec_ctx, AOME_GET_LAST_QUANTIZER_64, &quantizer_64);
    aom_codec_control(&codec_ctx, AOME_GET_LAST_QUANTIZER, &quantizer);
    aom_codec_control(&codec_ctx, AV1E_GET_NUM_OPERATING_POINTS, &num_operating_points);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}