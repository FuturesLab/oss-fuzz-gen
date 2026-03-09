// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST at aomcx.h:1986:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE at aomcx.h:2362:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION at aomcx.h:2040:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF at aomcx.h:2323:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE at aomcx.h:1995:1 in aomcx.h
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdlib>
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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int) * 2) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Use the first few bytes of data as integer parameters
    unsigned int param1 = *(reinterpret_cast<const unsigned int*>(Data));
    unsigned int param2 = *(reinterpret_cast<const unsigned int*>(Data + sizeof(unsigned int)));

    // Attempt to invoke the target functions with the parameters
    aom_codec_err_t res;

    res = aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST(&codec_ctx, 0, param1);
    if (res != AOM_CODEC_OK) {
        // Handle error or log
    }

    res = aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE(&codec_ctx, 0, param1);
    if (res != AOM_CODEC_OK) {
        // Handle error or log
    }

    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec_ctx, 0, param1);
    if (res != AOM_CODEC_OK) {
        // Handle error or log
    }

    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION(&codec_ctx, 0, param1);
    if (res != AOM_CODEC_OK) {
        // Handle error or log
    }

    res = aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF(&codec_ctx, 0, param1);
    if (res != AOM_CODEC_OK) {
        // Handle error or log
    }

    res = aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE(&codec_ctx, 0, param1);
    if (res != AOM_CODEC_OK) {
        // Handle error or log
    }

    // Cleanup codec context if needed
    aom_codec_destroy(&codec_ctx);

    return 0;
}