// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION at aomcx.h:2040:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS at aomcx.h:2387:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF at aomcx.h:2323:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_CDEF at aomcx.h:2037:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FP_MT at aomcx.h:2329:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE at aomcx.h:2362:1 in aomcx.h
#include <iostream>
#include <cstring>
#include <cstdint>
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

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    codec_ctx.name = "fuzz_test_codec";
    codec_ctx.iface = nullptr; // Normally set to a valid iface
    codec_ctx.init_flags = 0; // No flags for initialization

    // Example of invoking the target functions with various states
    aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION(&codec_ctx, 0, Data[0] % 2);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS(&codec_ctx, 0, Data[1] % 2);
    aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF(&codec_ctx, 0, 0);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_CDEF(&codec_ctx, 0, Data[2] % 2);
    aom_codec_control_typechecked_AV1E_SET_FP_MT(&codec_ctx, 0, Data[3] % 4);
    aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE(&codec_ctx, 0, Data[4] % 3);

    return 0;
}