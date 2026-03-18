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
#include "aom/aom_integer.h"
#include "aom/aom_image.h"
#include "aom/aom_codec.h"
#include "aom/aom_frame_buffer.h"
#include "aom/aom_encoder.h"
#include "aom/aom_external_partition.h"
#include "aom/aom.h"
#include "aom/aom_decoder.h"
#include "aom/aomcx.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));
    codec.iface = aom_codec_av1_cx();

    // Initialize codec
    if (aom_codec_enc_init(&codec, codec.iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Extract integer from input data
    int control_value;
    memcpy(&control_value, Data, sizeof(int));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY
    aom_codec_control(&codec, AV1E_SET_ENABLE_OVERLAY, control_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA
    aom_codec_control(&codec, AV1E_SET_ENABLE_CFL_INTRA, control_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL
    aom_codec_control(&codec, AV1E_SET_LOOPFILTER_CONTROL, control_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE
    aom_codec_control(&codec, AV1E_SET_COLOR_RANGE, control_value);

    // Fuzz aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS
    int num_operating_points = 0;
    aom_codec_control(&codec, AV1E_GET_NUM_OPERATING_POINTS, &num_operating_points);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS
    aom_codec_control(&codec, AV1E_SET_TRANSFER_CHARACTERISTICS, control_value);

    // Cleanup
    aom_codec_destroy(&codec);

    return 0;
}