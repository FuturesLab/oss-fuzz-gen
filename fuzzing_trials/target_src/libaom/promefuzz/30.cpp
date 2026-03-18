// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX at aomcx.h:2025:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS at aomcx.h:2004:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC at aomcx.h:2371:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE at aomcx.h:2022:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE at aomcx.h:2383:1 in aomcx.h
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
extern "C" {
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aom_decoder.h"
#include "aomcx.h"
#include "aomdx.h"
}

#include <cstdint>
#include <cstring>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 3) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Dummy interface and private data
    codec_ctx.iface = aom_codec_av1_cx();
    codec_ctx.priv = nullptr;

    // Prepare dummy file if needed
    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    if (dummy_file.is_open()) {
        dummy_file.write(reinterpret_cast<const char*>(Data), Size);
        dummy_file.close();
    }

    // Extract integer values from input Data
    int param1 = *reinterpret_cast<const int*>(Data);
    int param2 = *reinterpret_cast<const int*>(Data + sizeof(int));
    int param3 = *reinterpret_cast<const int*>(Data + 2 * sizeof(int));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES
    aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec_ctx, AV1E_SET_COLOR_PRIMARIES, param1);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX
    aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX(&codec_ctx, AV1E_SET_TARGET_SEQ_LEVEL_IDX, param2);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS
    aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS(&codec_ctx, AV1E_SET_MATRIX_COEFFICIENTS, param1);

    // Fuzz aom_codec_control_typechecked_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC
    int high_motion_content;
    aom_codec_control_typechecked_AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC(&codec_ctx, AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC, &high_motion_content);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE
    int render_size[2] = {param1, param2};
    aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE(&codec_ctx, AV1E_SET_RENDER_SIZE, render_size);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE
    aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE(&codec_ctx, AV1E_SET_SCREEN_CONTENT_DETECTION_MODE, param3);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}