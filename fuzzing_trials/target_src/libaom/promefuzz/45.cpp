// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD at aomcx.h:1919:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TILE_ROWS at aomcx.h:1965:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_QM at aomcx.h:2052:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING at aomcx.h:1974:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP at aomcx.h:2344:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL at aomcx.h:1968:1 in aomcx.h
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
#include <cstdlib>
#include <cstdio>
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

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Extract integer from input data
    int control_value;
    memcpy(&control_value, Data, sizeof(int));

    // Dummy member to satisfy the third argument requirement
    unsigned int dummy_member = 0;

    // Fuzz aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD
    aom_codec_err_t res1 = aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD(&codec_ctx, control_value, dummy_member);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TILE_ROWS
    aom_codec_err_t res2 = aom_codec_control_typechecked_AV1E_SET_TILE_ROWS(&codec_ctx, control_value, dummy_member);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_QM
    aom_codec_err_t res3 = aom_codec_control_typechecked_AV1E_SET_ENABLE_QM(&codec_ctx, control_value, dummy_member);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING
    aom_codec_err_t res4 = aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING(&codec_ctx, control_value, dummy_member);

    // Fuzz aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP
    aom_codec_err_t res5 = aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP(&codec_ctx, control_value, dummy_member);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL
    aom_codec_err_t res6 = aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL(&codec_ctx, control_value, dummy_member);

    // Handle errors and cleanup
    if (res1 != AOM_CODEC_OK || res2 != AOM_CODEC_OK || res3 != AOM_CODEC_OK ||
        res4 != AOM_CODEC_OK || res5 != AOM_CODEC_OK || res6 != AOM_CODEC_OK) {
        fprintf(stderr, "Error occurred in codec control functions\n");
    }

    return 0;
}